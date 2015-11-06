/** 
 * @project Testa_assembler
 *
 * @brief Arquivo unico do projeto
 * @file Main.c
 * @author Cleber Jorge Amaral
 * @date Oct/2015
 *
 * Neste programa realizamos testes com diferentes estruturas l�gicas para verificar
 * como o compilador monta a l�gica (assembly). S�o feitos testes de tempo que servem
 * para dar uma melhor dimens�o da efici�ncia do c�digo. Mas podemos verificar tamb�m
 * o assembly gerado.
 * Os testes foram validados em simula��o no proteus, atraves do osciloscopio virtual
 */
 
#include <reg52.h> 

sfr Porta_0 = 0x80;
sfr Porta_1 = 0x90;

void main() 
{
	unsigned char x = 0; 
	unsigned int i = 0;
	unsigned char c = 0;
	
	while (1)
	{

		/** Teste A
		 * Compara��o de tempo que leva  um la�o utilizando vari�vel inteira
		 * Na estrutura 1 ser� incrementado o valor de 0 at� 255, isso far� com que o compilador
		 * utilize estrutura de compara��o de bytes (comparar se chegou a 0x00FF atrav�s de CJNE)
		 * Na estrutura 2 ser� incrementado de 65280 at� 65536 (255 incrementos), com CJNEs, desta
		 * o compilador realiza compara��es dos dois registradores de 8bits de uma forma mais eficiente.
		 * Resultados (clock da CPU 11.0592MHz simulado pelo keil e validados no osciloscopio do proteus):
		 * Estrutura 1 consome 2.216797ms
		 * Estrutura 2 consome 1.939019ms
		 */
		
		/* Estrutura 1 */
		for (i = 0;i<0x00FF;i++); 

		/* Utilizado no proteus para medir o tempo */
		Porta_1 = ~Porta_1; 
		
		/* Estrutura 2 */
		for (i = 0xFFFF-0x00FF;i<0xFFFF;i++);

		/* Utilizado no proteus para medir o tempo */
		Porta_1 = ~Porta_1;

		/** Teste B (aqui podemos tamb�m comparar com os resultados do teste A j� que o range � 255 tamb�m)
		 * Compara��o de tempo que leva um la�o utilizando vari�vel char 
		 * Na estrutura 3 ser� incrementado o valor de 0 at� 255, compara��o com CJNE
		 * Na estrutura 4 ser� decrementado de 255 at� 0, utilizando DJNZ que � bem mais eficiente (decrementa e compara)
		 * Outro resultado que podemos obter seria comparando as estruturas 1 e 2
		 * com estas realizadas no teste B, que mostra a otimiza��o quando se trata
		 * de vari�veis int e char (para range que seriam suportados por uma char)
		 * Resultados (clock da CPU 11.0592MHz simulado pelo keil e validados no osciloscopio do proteus):
		 * Estrutura 3 consome 0,832248ms
		 * Estrutura 4 consome 0,55447ms
		 */

		/* Estrutura 3 */
	  for (c = 0;c<0xFF;c++);
		
		/* Utilizado no proteus para medir o tempo */
		Porta_1 = ~Porta_1;

		/* Estrutura 4 */
		for (c = 0xFF;c > 0;c--);

		/* Utilizado no proteus para medir o tempo */
		Porta_1 = ~Porta_1;


		/** Teste C
		 * Compara��o de tempo que leva um la�o utilizando vari�vel char 
		 * Na estrutura 5 ser� incrementado o valor de 0 at� 128 (meio de escala), utilizando CNJE.
		 * Na estrutura 6 ser� decrementado de 128 at� 0 (inicio de escala), utilizando DJNZ.
		 * Resultados (clock da CPU 11.0592MHz simulado pelo keil e validados no osciloscopio do proteus):
		 * Estrutura 5 consome 0,418836ms
		 * Estrutura 6 consome 0,278862ms
		 */

		/* Estrutura 5 */
		for (c = 0;c < 0x80;c++);

		/* Utilizado no proteus para medir o tempo */
		Porta_1 = ~Porta_1;

		/* Estrutura 6 */
		for (c = 0x80;c > 0;c--);

		/* Utilizado no proteus para medir o tempo */
		Porta_1 = ~Porta_1;


		Porta_0 = x++;
	}
}