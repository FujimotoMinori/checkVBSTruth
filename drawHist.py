import ROOT
from array import array
from ROOT import TCanvas
from ROOT import gROOT
from ROOT import *
gROOT.SetBatch()

# ATLAS Style
# this path below is not available. Just for reference
#ROOT.gROOT.LoadMacro("/nfs/dust/atlas/user/jeongj/atlas_Style/AtlasUtils.C")
#ROOT.gROOT.LoadMacro("/nfs/dust/atlas/user/jeongj/atlas_Style/AtlasStyle.C")
#ROOT.gROOT.LoadMacro("/nfs/dust/atlas/user/jeongj/atlas_Style/AtlasLabels.C")

#SetAtlasStyle()

def setHistoStyle( h, lc, ms ):
    size = 0.045
    h.SetLineColor(lc)
    h.SetLineWidth(2)
    #h.SetMarkerStyle(ms)
    h.SetMarkerColor(lc)
    h.SetTitleOffset( 1.3, "X" )
    h.SetTitleOffset( 1.3, "Y" )
    h.SetTitleSize( size, "X" )
    h.SetTitleSize( size, "Y" )
    h.SetLabelSize( size, "X" )
    h.SetLabelSize( size, "Y" )

def setCanvasStyle( c ):
    c.SetTicks()
    c.SetLeftMargin(0.15) #0.15
    c.SetRightMargin(0.05)
    c.SetTopMargin(0.05)
    c.SetBottomMargin(0.15)

def SetLegendStyle(l):
    l.SetTextSize(0.05);
    l.SetTextFont(42);
    l.SetFillStyle(0);
    l.SetFillColor(0);
    l.SetBorderSize(0);

f1 = ROOT.TFile("output.root")
f2 = ROOT.TFile("WZjjoutput.root")

hnames = []

# key here is the histogram. Get list of names of the histograms and put it in an array called hnames.
for key in f1.GetListOfKeys():
    n = key.GetName()
    # here one can put if statement to select specific histograms containing/starting/ending a word "A"
    hnames += [n]


# To select histograms, instead of using for loop of the list of keys, one can specify each names of the histogram. For example,
'''
hnames += "my-histogram1"
hnames += "my-histogram2"
'''
# Or directly use t1 = f.Get("my-histogram1"), t2 = f.Get("my-histogram2") in the below for loop

# for loop of histograms
for i in range(len(hnames)):
    c = TCanvas("c_%s" %(i)) # for each histogram, make a canvas named "c_histogram"
    t1 = f1.Get(hnames[i])     # t is the histogram object: TH1 or TH2
    t2 = f2.Get(hnames[i])     # t is the histogram object: TH1 or TH2

    t1.SetStats(0)            # 0: do not show statistics box
    t2.SetStats(0)            # 0: do not show statistics box

    #Scatter plot
    #t.SetMarkerStyle(20) # 20 as default; 7 = full dot medium
    #t.SetMarkerColor(1)  # 1 = kBlack
    #t.Draw("p")
    setCanvasStyle( c )

    setHistoStyle(t1, ROOT.kBlue+1, 20)
    setHistoStyle(t2, ROOT.kRed+1,25)

    t1.GetYaxis().SetRangeUser(0.85,1.1)  # set the position of the Label of Y axis away from the Y axis.
    t2.GetYaxis().SetRangeUser(0.85,1.1)  # set the position of the Label of Y axis away from the Y axis.
    #t.GetYaxis().SetTitleOffset(1.4)  # set the position of the Label of Y axis away from the Y axis.
    #t.GetZaxis().SetTitle("Average rate [Hz]") # Z axis is defined for 2D histogram, the palette axis.
    #t.GetZaxis().SetTitleOffset(1.2) # set the position of the Label of palette(Z) axis.
    #gStyle.SetPalette(1)             # 1: default colour scheme for 2D histogram. Specify in case in use of ATLAS style as the colour is set differently. 
    #gStyle.SetPadLeftMargin(0.15)    
    #gStyle.SetPadRightMargin(0.20)
    #ROOT.ATLASLabel(0.6, 0.87, "internal", ROOT.kBlack) # must be put after t.Draw() as it is written on 
    lg = TLegend(0.62, 0.7, 1.00, 0.90) # 0.62,0.3,1.00,0.50
    SetLegendStyle(lg)
    #lg.SetHeader("Data ID=123 (N=100)")
    lg.AddEntry( t1, "defalut MC", "lp")
    #lg.AddEntry( t1, "Mean = " + format(t1.GetMean(), '.2f'), "")
    #lg.AddEntry( t1, "Std. Dev. = " + format(t1.GetStdDev(), '.2f'), "")
    lg.AddEntry( t2, "new MC", "lp")
    #lg.AddEntry( t2, "Mean = " + format(t2.GetMean(), '.2f'), "")
    #lg.AddEntry( t2, "Std. Dev. = " + format(t2.GetStdDev(), '.2f'), "")

    #
    c.cd()
    #t1.Draw("HIST E1")
    t1.Draw()
    #t2.Draw("HIST E1 SAME")
    t2.Draw("SAME")
    lg.Draw()

    #c.SetLogy();         # Set log scale for Y axis in the canvas.
    c.Update()
    c.Print("%s.png" %(hnames[i]), 'png') # Save the figure in the 'eps' format.

