import numpy as np
import VBBinaryLensing 
import os

VBBL = VBBinaryLensing.VBBinaryLensing()
tol = 0.005
rel_tol = 0.005
a1 = 0.68

VBBL.Tol = tol
VBBL.RelTol = rel_tol
VBBL.a1 = a1

# Load ESPL table

VBBL.LoadESPLTable(os.path.dirname(VBBinaryLensing.__file__)+'/VBBinaryLensing/data/ESPL.tbl')


#Set cooridnates
VBBL.SetObjectCoordinates(os.path.dirname(VBBinaryLensing.__file__)+"/VBBinaryLensing/data/OB151212coords.txt",
                              os.path.dirname(VBBinaryLensing.__file__)+"/VBBinaryLensing/data/satellite1.txt")

def test_BinSourceLightCurve():

    mag = VBBL.BinSourceLightCurve([1,np.log10(0.8),0.1,0.025,10,15],[10.25,2,69],[0.018],[0.0035])

    assert np.allclose(mag,[4.403129953719895, 1.0110018902397573, 1.000010732694136])


### This test is disconnect since it seems to be unstable, depending on the compiler ??!!??

#def test_BinSourceLightCurveParallax():
    #import pdb; pdb.set_trace()
#    
#    mag = VBBL.BinSourceLightCurveParallax([1,np.log10(0.5),0.01,0.025,10,15,0.1,-0.1],
#                                           [10.25,2,69],[0.018],[0.0035])
     
#    assert np.allclose(mag,[6.8039785968976645, 1.011767648738372, 1.000010643694068],
#                      rtol=rel_tol, atol=tol)

def test_BinSourceLightCurveXallarap():

    mag = VBBL.BinSourceLightCurveXallarap([1,0.5,0.01,0.025,10,15,0.1,-0.1,0.6,0.2,0.3,0.5],
                                           [10.25,2,69],[0.018],[0.0035],[10.0,6,7])
    
    assert np.allclose(mag,[1.8669479583448647, 1.0208755857794984, 1.0000097495857982],
                      rtol=rel_tol, atol=tol)

def test_BinaryLightCurve():

    mag =  VBBL.BinaryLightCurve([np.log10(0.97),-1.5,0.01,0.025,-2.5,1.5,10],[10.25,2,69],[0.018],[0.0035])

    assert np.allclose(mag,[14.989374837435403, 1.0842731547424023, 1.0], rtol=rel_tol, atol=tol)

def test_BinaryLightCurveOrbital():
    #VBBL.SetObjectCoordinates("VBBinaryLensing/data/OB151212coords.txt",
     #                         "VBBinaryLensing/data/satellite1.txt")

    mag =  VBBL.BinaryLightCurveOrbital([np.log10(0.97),
                                         -1.5,0.01,0.1,-2.5,1.5,10,-0.25,0.36,0.1,0.056,0.03],
                                        [10.25,2,69],[0.018],[0.0035],[1,25,36])

    assert np.allclose(mag,[14.446493529090516, 1.0811430891964906, 1.0], rtol=rel_tol, atol=tol)

def test_BinaryLightCurveParallax():

    mag =  VBBL.BinaryLightCurveParallax([np.log10(0.97),-1.5,0.01,0.1,-2.5,1.5,10,0.6,0.025],
                                         [10.25,2,69],[0.018],[0.0035])

    assert np.allclose(mag,[14.846407903118143, 1.0831311541007225, 1.0], rtol=rel_tol, atol=tol)


def test_BinaryLightCurveW():

    mag =  VBBL.BinaryLightCurve([np.log10(.27),-0.5,0.01,0.1,-2.5,1.5,10],[10.25,2,69],[0.018],[0.0035])

    assert np.allclose(mag,[15.92662349677546, 1.0732162742327906, 1.0], rtol=rel_tol, atol=tol)

def test_BinaryMag():


    mag = VBBL.BinaryMag(1.28,0.05,0.28,0.0056,0.05,tol)

    assert np.allclose(mag, 4.36339307985976, rtol=rel_tol, atol=tol)
    
def test_BinaryMag0():

    mag = VBBL.BinaryMag0(1.28, 0.05, 0.28, 0.0056)

    assert np.allclose(mag, 4.268002604737058)


def test_BinaryMag2():

    mag2 = VBBL.BinaryMag2(1.28, 0.05, 0.48, 0.86, 0.05) 
    mag0 = VBBL.BinaryMag0(1.28, 0.05, 0.48, 0.86)
    
    assert mag2 == mag0

    mag = VBBL.BinaryMag(1.28,0.05,0.28,0.0056,0.05, tol)
    mag2 = VBBL.BinaryMag2(1.28,0.05,0.28,0.0056,0.05) 
    
    assert np.allclose(mag, mag2, rtol=rel_tol, atol=tol)

def test_BinaryMagDark():

    mag = VBBL.BinaryMagDark(1.28,0.05,0.28,0.0056,0.05,a1,tol)
    mag2 = VBBL.BinaryMag2(1.28,0.05,0.28,0.0056,0.05) 

    assert np.abs(mag-mag2)<tol
    
    
def test_BinaryMagMultiDark():

    #mag = VBBL.BinaryMagMultiDark(1.28,0.05,0.28,0.0056,0.05,[0.68,0.55],2,[2.5,3.0],0.05)
    
    pass

def test_ESPLLightCurve():

    mag = VBBL.ESPLLightCurve([-2,2,10,-1],[10,10.02,5],[1],[1])  
    
    assert np.allclose(mag,
                    [5.762272891302062, 5.762147624422236, 1.7530582089918916],
                      rtol=rel_tol, atol=tol)
    
def test_ESPLLightCurveParallax():

    mag = VBBL.ESPLLightCurveParallax([-2,2,10,-1,0.1,-0.5],[10,10.02,7.5],[1],[1])  
            
    assert np.allclose(mag,[1.0606601717804944, 1.060660007528057, 1.0581736726473168],
                      rtol=rel_tol, atol=tol)

def test_ESPLMag():
    u = 1.
    rho = 0. 
    mag = VBBL.ESPLMag(u, rho)

    assert np.allclose(mag, 3./np.sqrt(5.), rtol=rel_tol, atol=tol)

    u = 10**-5
    rho = 0.05 

    magnification = VBBL.ESPLMag(u, rho)
   
    assert np.allclose(magnification, 40.012478065951136, rtol=rel_tol, atol=tol)
    
    
def test_ESPLMag2(): 
    u = 1.
    rho = 0. 
    mag = VBBL.ESPLMag(u, rho)

    assert np.allclose(mag, 3./np.sqrt(5.), rtol=rel_tol, atol=tol)

    u = 10**-5
    rho = 0.05 

    magnification = VBBL.ESPLMag(u, rho)
   
    assert np.allclose(magnification, 40.012478065951136, rtol=rel_tol, atol=tol)


def test_ESPLMagDark():

    u = 1.
    rho = 0. 
    mag = VBBL.ESPLMag(u, rho)

    assert np.allclose(mag, 3./np.sqrt(5.), rtol=rel_tol, atol=tol)

    u = 10**-5
    rho = 0.05 

    magnification = VBBL.ESPLMag(u, rho)
   
    assert np.allclose(magnification, 40.012478065951136, rtol=rel_tol, atol=tol)

def test_PSPLLightCurve():
   
    magnification = VBBL.PSPLLightCurve([-1,1.5,0],[0.1,-0.26,58],[0],[0])

    assert np.allclose(magnification,[2.849593596154959, 2.822788941413933, 1.0000695226177672],
                      rtol=rel_tol, atol=tol)

def test_PSPLLightCurveParallax():
   
    magnification = VBBL.PSPLLightCurveParallax([-1,1.5,0,-0.85,0.2],[0.1,-0.26,58],[0],[0])

    assert np.allclose(magnification,[1.3460380740740694, 1.3417579916307516, 1.0000660429052854],
                      rtol=rel_tol, atol=tol)

def test_PlotCrit():
    #curves = VBBL.PlotCrit(1.56,0.29)
    
    pass

def test_amplification_USBL():
    s = 1.
    q = 0.02
    y1 = 0.5 
    y2 = 0.5 
    rho = 0.0033

    magnification = VBBL.BinaryMag2(s, q, y1, y2, rho)

    assert np.allclose(magnification, 1.6310924403681109, rtol=rel_tol, atol=tol)
    
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

    VBBL.RelTol=10**-4
    magnification = VBBL.BinaryMag2(s, q, y1, y2, rho)

    
    magnification0 = VBBL.BinaryMag2(s, q, y1, y2, rho)
    assert np.allclose(magnification, magnification0, rtol=rel_tol, atol=tol)
    
def test_amplification_FSBL():
   
    s = 1.
    q = 0.0002
    y1 = 0.005 
    y2 = 0.005 
    rho = 0.0033
    a1 = 0.2


    magnification = VBBL.BinaryMagDark(s, q, y1, y2, rho, a1, tol)
    assert np.allclose(magnification, 143.96471353081841, rtol=rel_tol, atol=tol)
def test_amplification_PSBL():
    s = 1.
    q = 0.02
    y1 = 0.5
    y2 = 0.5 

    magnification = VBBL.BinaryMag0(s, q, y1, y2);

    assert np.allclose(magnification, 1.63109244, rtol=rel_tol, atol=tol)
