#!/usr/bin/python
# -*- coding: utf-8 -*-
# ===============================
# Paulo Trigo Silva (PTS)
# MAR.2017
# ===============================



print( "\n----- Um Exemplo -----" )

def f( v="umParametro" ):
   def g(): return v
   return g

x = f()
print( x )
print( x() )

print( "\n----- Outro Exemplo -----" )

def f( v1="umParametro" ):
   def g( v2="outroParametro" ):
      def h(): return v1 + "//" + v2
      return h
   return g

x = f()
print( x )
print( x() )
print( x()() )
print( f( "http:" )( "www" )() )



#__________________________________________________________________________
# Experiencias previas (de apoio 'a compreensao do @decorator)
# funcao que devolve outra funcao; notar que:
# - a variavel v existe no "scope" das funcoes locais
# IMPORTANTE:
# esta construcao permite formular a nocao de classe, onde:
# - c, e' uma classe
# - s_m, e' o "scope" (contexto) dos metodos
# - m, e' um metodo
#__________________________________________________________________________
def c( v=0 ):
   def s_m( x ):
      if x == 1:
         def m( y ): return y**2 + v
      elif x == 2:
         def m( y ): return "< " + str(y) + " >" + "$ " + str(v) + " $"
      else:
         def m(): return "---"
      return m
   return s_m

print( "\nExperiencias previas (funcao que devolve uma funcao):" )
o = c()
# notar que o e' uma funcao
print( o( 1 ) )
print()
print( o( 1 )( 100 ) )
print( o( 2 )( "ola" ) )
print( o( 3 )() )
# OU
print( c()( 1 )( 100 ) )
print( c( "www" )( 2 )( "ola" ) )
print( c()( 3 )() )
#__________________________________________________________________________



#__________________________________________________________________________
# seja:
# f( g ( h( x ) ) )
# se quisermos definir a funcao h com o resultado desta composição
# ou seja, se pretendermos fazer:
# h = f( g ( h ) )
# IMPORTANTE: notar que h e' uma função (f o g)
# e não o resultado da invocação das funções g e f
# então escreve-se
# @f
# @g
# def h(): ...
#
# E caso diz-se que f e g são "decorators" de h
#__________________________________________________________________________

# Exemplo:
def f( fn ):
   def local():
      s = "< " + fn() + " >"
      return s
   return local

def g( fn ):
   def local():
      s = "# " + fn() + " #"
      return s
   return local
   
print( "\nVersao com sintaxe @decorator:" )
@f
@g
def h():
   s = "h"
   return s

print( h() )

print( "\nVersao com definicao directa:" )
def h():
   s = "h"
   return s

h = f( g ( h ) )
print( h() )
