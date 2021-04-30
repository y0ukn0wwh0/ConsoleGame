# -*- coding: cp1252 -*-
# ===============================
# author: Paulo Trigo Silva (PTS)
# since: MAR.2017
# ===============================

# PARA TESTAR:
# escrever em linha de comando as seguintes instrucoes:
# python c_Controlo.py -a 123
# python c_Controlo.py -x 123
# python c_Controlo.py --paramA=123456789
# python c_Controlo.py --paramA=123456789 -c "CCCCC"



#______________________________________________________________________________
# Importar modulos
from x_singleton import singleton
from e_Config import e_Config
import sys



#______________________________________________________________________________
# Exemplo de uma classe controlo a ser iniciada com opcoes de comando de linha
@singleton
class c_UmControlo:
   def start( self, argv ):
      # o construtor de e_Config define as opcoes de omissao
      e = e_Config()
      # as opcoes de omissao sao combinadas com as opcoes passadas em comando de linha
      e.configurar( argv )
      # obter o conjunto final de opcoes
      opcaoValor = e.obterOpcaoValor()

      # converter as opcoes em valores a usar no sistema
      for (opcao, valor) in opcaoValor:                
         if   opcao in ("-a", "--paramA"): p1 = valor                 
         elif opcao in ("-b", "--paramB"): p2 = valor
         elif opcao in ("-c", "--paramC"): p3 = valor

      print( "start" )
      print( "a=%s, b=%s, c=%s" % (p1, p2, p3) )




#______________________________________________________________________________
# Um "main" que incia um "Controlo" com uma lista de opcoes de comando de linha
def main( argv=None ):    
   c = c_UmControlo()
   c.start( argv )




#______________________________________________________________________________
# O "main" deste modulo (caso o modulo nao seja carregado de outro modulo)
if __name__ == "__main__":
   # sys.argv contem as opcoes passadas em comando de linha
   main( sys.argv )






