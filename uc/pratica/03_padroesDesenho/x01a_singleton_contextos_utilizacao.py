#!/usr/bin/python
# -*- coding: utf-8 -*-
# ===============================
# Paulo Trigo Silva (PTS)
# MAR.2017
# ===============================


# usar o singleton noutro contexto
from x01_singleton import C, D

print( "---\\outro-modulo//---" )

c1=C()
c1.f()
c1.inc()

c2=C()
c2.f()


def f():
   print( "---\\outro-modulo::f_a//---" )
   c=C()
   c.f()
   c.inc()
   c.f()

   print( "---\\outro-modulo::f_b//---" )
   
   d=D()
   d.inc()
   d.f()



class H:
   def __init__( self ):
      print( "---\\outro-modulo::class::H::__init__()//---" )
      c=C()
      c.f()
      c.inc()
      c.f()

   def m( self ):
      print( "---\\outro-modulo::class::H::m()//---" )
      c=C()
      c.inc()
      c.f()
        


#_______________________________________________________________________________
def main():
    f()
    H().m()
    print( "---\\outro-modulo::main//---" )
    c=C()
    c.inc()
    c.f()
#_______________________________________________________________________________



# tecnica para permitir que o modulo possa ser:
# - importado por outro
# - executado directamente
# a variavel "python" __name__ toma o valor "__main__"
# caso o modulo seja excutado directamente (não importando)
#_______________________________________________________________________________
if __name__ == "__main__":
    main()


