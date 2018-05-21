#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define catidad_pulsos  8000
#define pulso_v_h 6000
double omp_get_wtime(void);
/** Decalaracion de funcion para autocorrelacion */
void correlacion(float matriz[501][801],int fichero);

int main(void)
{	
	/** Variable para contar el tiempo de ejecucion */
	double start, end;
   	start = omp_get_wtime();
   	/** Variable para lectura de archivo */
 	FILE *archivo;
 	/** Variable que almacena la posicion del valid sample */ 	
  	int posicion_valid_sample = 1;
  	/** Variable para guardar el dato de fase y cuadratura */
 	float dato;
 	/** Variable para guardar el valor del Valid sample */
 	uint16_t validSamples;
 	/** Variables utilizadas en los ciclos for */
 	int suma = 0;
 	int validSample[catidad_pulsos];
 	int j = 0;
 	int g;
 	int p = 1;
	/** Arreglo para almacenar el valor absoluto del canal vertical */
	float pulsos_vertical[501];
	/** Arreglo para almacenar el valor absoluto del canal horizontal */
	float pulsos_horizontal[501];
	/** Matriz que almacena los datos del canal vertical */
	float matriz_v[501][801];
	/** Matriz que almacena los datos del canal horizontal */
	float matriz_h[501][801];
	/** Variable que almacena la muestra para fase*/
	float pul_fase;
	/** Variable que almacena la muestra para cuadratura*/
	float pul_cuadratura;
	/** Abro el archivo pulso.iq */
 	archivo = fopen("pulsos.iq","rb");

 	if (archivo == NULL)
 	{
 		exit(1);
 	}
 	else
    { 		
    	while (!feof(archivo))
		{
			int jj = 0;
			float valor_absoluto = 0;
	   		fread(&validSamples, sizeof(uint16_t), 1, archivo);
	   		validSample[j] = validSamples;
	   		suma = suma + 4*validSample[j]; 
			/** Calculo el valor absoluto del pulso correspondiente al canal vertical y lo guardo en un arreglo */
			for(int i = 0; i < 2*validSamples; i = i+2)
			{	
	        	fread(&dato, sizeof(float), 1, archivo);
	            pul_fase = dato;
	            fread(&dato, sizeof(float), 1, archivo);
	            pul_cuadratura = dato; 
	            valor_absoluto = sqrt(pow(pul_fase, 2)+pow(pul_cuadratura , 2));
	            pulsos_vertical[jj] = valor_absoluto;
	            jj++;
			}
			jj = 0;
			/** Calculo el valor absoluto del pulso correspondiente al canal horizontal y lo guardo en un arreglo */
     		for (int i = 0; i < 2 * validSamples; i++)     
			{
			    fread(&dato, sizeof(float), 1, archivo);
			    pul_fase = dato;
			    fread(&dato, sizeof(float), 1, archivo);
			    pul_cuadratura = dato; 
			    i++;
		        valor_absoluto = sqrt(pow(pul_fase, 2)+pow(pul_cuadratura , 2));		            
		        pulsos_horizontal[jj] = valor_absoluto;
			    jj++;
			}
			/** Genero la matriz vertical a medida que voy obteniedo los pulsos para el canal vertical*/
			float gate_muestra = (0.5 * validSamples) / 250;
			int aux = 0;
			float real = 0;
			float decimal = 0;
			int gate_muestra_actual;
			float gate_muestra_actual_aux;
			int ii;
			g = 1;
			gate_muestra_actual = (int)gate_muestra; //Valor de muestra inicial
			decimal = gate_muestra - (int)gate_muestra;
			for (ii = 0; ii < validSamples; ii++)
    		{
      			if (aux < gate_muestra_actual)
		        {
					real = real + pulsos_vertical[ii];
					aux++;
					if(g == 500 && aux == gate_muestra_actual )
					{	
						ii--;
					}	
		        }
		      	else
		        {
					matriz_v[g][p] = real/aux;
					if(g == 500)
					{
						break;	
					} 
    				ii--;
					g++;
					aux = 0;
					real = 0;
					gate_muestra_actual_aux = gate_muestra + decimal;
    				decimal = gate_muestra_actual_aux - (int)gate_muestra_actual_aux;
    				gate_muestra_actual = (int)gate_muestra_actual_aux; //Nuevo valor de muestra
		        }
    		}
    		aux = 0;
			real = 0;
			/** Genero la matriz horizontal a medida que voy obteniedo los pulsos para el canal horizontal*/
    		int gg = 1;
    		int iii;
    		int gate_muestra_actual_h;
    		float decimal_h = 0;
    		float gate_muestra_actual_aux_h;
    		gate_muestra_actual_h = (int)gate_muestra; //Valor de muestra inicial
			decimal_h = gate_muestra - (int)gate_muestra;
    		for (iii = 0; iii < validSamples; iii++)
    		{
		    	if (aux < gate_muestra_actual_h)
		        {
					real = real + pulsos_horizontal[iii];
					aux++;
					if(gg == 500 && aux == gate_muestra_actual_h )
					{	
						iii--;
					}
		        }
		      	else
		        {
					matriz_h[gg][p] = real / aux;
					if(gg == 500)
					{
						break;	
					}
					iii--;
					gg++;
					aux = 0;
					real = 0;
					gate_muestra_actual_aux_h = gate_muestra + decimal_h;
					decimal_h = gate_muestra_actual_aux_h -(int)gate_muestra_actual_aux_h;
					gate_muestra_actual_h = (int)gate_muestra_actual_aux_h; //Nuevo valor de muestra
		        }
    		}
			if(posicion_valid_sample == 800)
	   		{
	   			break;
	   		}
	   		p++; 
			j++;
	   		posicion_valid_sample++;
		}
    }
    fclose(archivo);
    /** Calculo autocorrelacion del canal vertical */
	correlacion(matriz_v,1);
    /** Calculo autocorrelacion del canal vertical */
	correlacion(matriz_h,2);
	end= omp_get_wtime(); //guardo el tiempo final de ejecucion
	printf("El tiempo transcurrido es: %f segundos.\n", end-start);
    return 0;
}
/**
 * @brief [Calculo la autocorrelacion del canal horizontal y canal vertical segun corresponda]
 * 
 * 
 * @param matriz [recibe como parametro matriz vertical o matriz horizontal]
 * @param fichero [indica si el fichero de escritura es para autocorrelacion vertical o horizontal. Si vale 1 es vertical si vale 2 es horizontal]
 */
void correlacion(float matriz[501][801],int fichero)
{
	float resul_correlacion = 0;
	float autocorrelacion[501] = {0};
    FILE *correlacion;
    int ii;
    if(fichero == 1) 
    {
    	correlacion = fopen("correlacion_vertical.bin","wb");
    }
    if(fichero == 2)
    {
    	correlacion = fopen("correlacion_horizontal.bin","wb");
   	}
   	int c,f;
    for(f = 1; f < 501; f++)	
	{
		for(c = 1; c < 800; c++)
		{
			resul_correlacion = resul_correlacion + (matriz[f][c] * matriz[f][c+1]);
		}
		autocorrelacion[f] = resul_correlacion / 800;
		resul_correlacion = 0;
	}	    
    if(fichero == 1)
    {
	    for(ii = 1; ii < 501; ii++)
    	{
			fprintf(correlacion,"Canal Vertical [%d]\n%.10f\n",ii,autocorrelacion[ii]);	    
    	}		
    }
    if(fichero == 2)
    {
    	for(ii = 1; ii < 501; ii++)
    	{
			fprintf(correlacion,"Canal Horizontal [%d]\n%.10f\n",ii,autocorrelacion[ii]);	    
    	}		
    }
		
	fclose(correlacion);	    
}
