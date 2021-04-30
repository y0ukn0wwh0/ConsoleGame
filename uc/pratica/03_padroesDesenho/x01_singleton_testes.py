#!/usr/bin/python
# -*- coding: utf-8 -*-
# ===============================
# Paulo Trigo Silva (PTS)
# MAR.2017
# ===============================
# 
# uma possivel implementacao de Singleton
# - descrita em: PEP 318
# (PEP = "Python Enhancement Proposals")



#______________________________________________________________________________
# esta funcao e' definida apenas 1 vez
def singleton( cls ):
    instances = {}
    def getInstance():
       if cls not in instances:
          instances[ cls ] = cls()
       return instances[ cls ]
    return getInstance
#______________________________________________________________________________




# se a classe C seguir o padrao Singleton
# e' decorada com a funcao "singleton"
@singleton
class C:
    def __init__( self ):
       self.c = 1

    def f( self ):
       print( self.c )

    def inc( self ):
       self.c += 1


c1=C()
c1.f()
c1.inc()

c2=C()
c2.f()

print( "---//\\---" )



# se a classe D seguir o padrao Singleton
# e' decorada com a funcao "singleton"
@singleton
class D:
    def __init__( self ):
       self.d = 1

    def f( self ):
       print( self.d )

    def inc( self ):
       self.d += 1



d1=D()
d1.f()
d1.inc()

d2=D()
d2.f()

print( "---//\\---" )
