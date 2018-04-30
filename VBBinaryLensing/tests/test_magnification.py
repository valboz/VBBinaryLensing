import numpy as np
import VBBinaryLensing

VBBL = VBBinaryLensing.VBBinaryLensing()

def test_ESPL_magnification():
    u = 1.
    rho = 0. 
    VBBL.LoadESPLTable("../data/ESPL.tbl")
    magnification = VBBL.ESPLMag2(u, rho)

    assert magnification ==  3./np.sqrt(5.)

def test_amplification_USBL():
    s = 1.
    q = 0.02
    y1 = 0.5 
    y2 = 0.5 
    rho = 0.0033


    magnification = VBBL.BinaryMag2(s, q, y1, y2, rho)

    assert np.allclose(magnification, 1.6310924403681109)
    
def test_amplification_USBL_far_from_caustics():
   
    s = 1.
    q = 0.02
    y1 = 0.5 
    y2 = 0.5 
    rho = 0.0033


    magnification = VBBL.BinaryMag2(s, q, y1, y2, rho)
    magnification0 = VBBL.BinaryMag0(s, q, y1, y2)
    assert magnification == magnification0
    
    
def test_amplification_USBL_with_RELTOL():
   
    s = 1.
    q = 0.0002
    y1 = 0.005 
    y2 = 0.005 
    rho = 0.0033


    magnification = VBBL.BinaryMag2(s, q, y1, y2, rho)
    VBBL.RelTol=10**-4
    
    magnification0 = VBBL.BinaryMag2(s, q, y1, y2, rho)
    assert (magnification-magnification0)<10**-4*magnification  
    
def test_amplification_FSBL():
   
    s = 1.
    q = 0.0002
    y1 = 0.005 
    y2 = 0.005 
    rho = 0.0033
    a1 = 0.2	

    magnification = VBBL.BinaryMagDark(s, q, y1, y2, rho, a1, 0.1)
    assert magnification == 144.38155079136942

def test_amplification_PSBL():
    s = 1.
    q = 0.02
    y1 = 0.5
    y2 = 0.5 

    magnification = VBBL.BinaryMag0(s, q, y1, y2);

    assert np.allclose(magnification, 1.63109244)
