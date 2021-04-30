# -*- coding: cp1252 -*-
# ===============================
# author: Paulo Trigo Silva (PTS)
# since: MAR.2017
# ===============================



#______________________________________________________________________________
# Importar modulos
import os
import sys
from getopt import getopt, error
# The "getopt" module helps scripts to parse the command line arguments in sys.argv.
# It supports the same conventions as the Unix getopt() function
# (including the special meanings of arguments of the form ‘-‘ and ‘--‘).




#______________________________________________________________________________
# Exemplo de uma classe Entity que trata as opcoes de iniciacao do sistema
# Neste exemplo o sistema tem 3 opcoes (a, b, c) que tem valor de omissao
# e que podem ser definidas por exemplo como opcao de comando de linha
class e_Config():
   def __init__( self ):
      # definicao dos pares (opcao, valor) de omissao
      # ou seja, os valores de omissao para as opcoes: a, b, c
      self.__opcaoValor = { \
         ("-a", "--paramA"): "aaa", \
         ("-b", "--paramB"): 555, \
         ("-c", "--paramC"): "RsR" }

  
   def configurar( self, argv ):
      try:
         try:
            (argv_opcaoValor, args) = \
               getopt( argv[1:], \
                       "a:b:c:", \
                       ["paramA=", "paramB=", "paramC="] )
         except error: raise Uso( self.uso() )
      except Uso as usoIncorrecto:
         sys.stderr.write( usoIncorrecto.msg )
         sys.exit( 2 )
         
      lista_parNome = self.__opcaoValor.keys()
      for (opcao, valor) in argv_opcaoValor:
         for parNome in lista_parNome:
            if opcao in parNome: self.__opcaoValor[ parNome ] = valor


   def obterOpcaoValor( self ):
      resultado = {}
      for parOpcao in self.__opcaoValor.keys():
         resultado[ parOpcao[ 0 ] ] = self.__opcaoValor[ parOpcao ]
      return list( resultado.items() )
   

   def uso( self ):
      esteFicheiro = os.path.basename( sys.argv[0] )
      aStr = ""
      aStr += "\n"
      aStr += "\n" + "Utilizacao:"
      aStr += "\n" +  "> " + esteFicheiro + " -a valorA -b valorB -c valorC"
      aStr += "\n" +  "ou"
      aStr += "\n" +  "> " + esteFicheiro + " --paramA valorA --paramB valorB --paramC valorC"
      aStr += "\n"
      return aStr




#______________________________________________________________________________
# Classe auxiliar
#(explora o tratamento de excepcoes e de decoradores como "getter" e "setter")
class Uso( Exception ):
   def __init__( self, msg ):
      self.msg = msg

   @property
   def msg( self ): return self.__msg

   @msg.setter
   def msg( self, value ):
      assert isinstance( value, str ), "PTS | msg: string expected"
      self.__msg = value
      
   @msg.deleter
   def msg( self ): self.__msg = ""




#______________________________________________________________________________
# O "main" deste modulo (caso o modulo nao seja carregado de outro modulo)
if __name__ == "__main__":
   # um teste
   argvTeste = ["f", '-a', 111, '-b', 222, '-c', 333]
   e = e_Config()
   e.configurar( argvTeste )
   print( e.obterOpcaoValor() )






