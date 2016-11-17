

curdir=`pwd`

for dir in reco refit

do

cd cards_sm13_1D_${dir}_2p7fb_CB/HCG/125

echo "$dir"

combineCards.py hzz4l_13TeV_4mu=hzz4l_4muS_13TeV.txt hzz4l_13TeV_4e=hzz4l_4eS_13TeV.txt hzz4l_13TeV_2e2mu=hzz4l_2e2muS_13TeV.txt  > comb_${dir}.txt

text2workspace.py comb_${dir}.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:floatingHiggsMass --PO higgsMassRange=115,135 --PO=muAsPOI -o FloatMass_comb_hzz2D_1D_${dir}.root

#combine -n 1D_${dir} -M MultiDimFit FloatMass_comb_hzz2D_1D_${dir}.root -m 125.0 -P MH --floatOtherPOIs=1 -D ${curdir}/cards_sm13_1Debe_${dir}_2p7fb_CB/HCG/125/higgsCombine1Debe_${dir}.MultiDimFit.mH125.12345.root:toys/toy_asimov --robustFit 1 --stepSize 0.005 --minimizerTolerance 0.005 --algo=singles --cl=0.68 -v 9 > ${curdir}/sm13_1D_${dir}.log 2>&1 &

#combine -n 1D_${dir} -M MultiDimFit FloatMass_comb_hzz2D_1D_${dir}.root -m 125.0 -P MH --floatOtherPOIs=1 --expectSignal=1 -t -1 --X-rtd TMCSO_PseudoAsimov=10000000 --saveWorkspace --saveToys --robustFit 1 --stepSize 0.001 --minimizerTolerance 0.001 -s 12345 --algo=singles --cl=0.68 -v 9 > ${curdir}/sm13_1D_${dir}.log 2>&1 &

combine -n 1D_${dir} -M MultiDimFit FloatMass_comb_hzz2D_1D_${dir}.root -m 125.0 -P MH --floatOtherPOIs=1 --expectSignal=1 -t -1 --saveWorkspace --saveToys --robustFit 1 --stepSize 0.001 --minimizerTolerance 0.001 -s 12345 --algo=singles --cl=0.68 -v 9 > ${curdir}/1D_${dir}.log 2>&1 &

cd -

done

