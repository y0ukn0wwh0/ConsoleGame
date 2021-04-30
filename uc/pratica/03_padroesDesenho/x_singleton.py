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
