

curdir=`pwd`

for dir in 1Debe_reco 1Debe_refit

do

cd cards_sm13_${dir}_2p7fb_CB/HCG/125

echo "$dir"

combineCards.py hzz4l_13TeV_4mu=hzz4l_4muS_13TeV.txt hzz4l_13TeV_4e=hzz4l_4eS_13TeV.txt hzz4l_13TeV_2e2mu=hzz4l_2e2muS_13TeV.txt  > comb_${dir}.txt

text2workspace.py comb_${dir}.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:floatingHiggsMass   --PO higgsMassRange=115,135 --PO=muAsPOI -o FloatMass_comb_hzz2D_${dir}.root

combine -n ${dir} -M MultiDimFit FloatMass_comb_hzz2D_${dir}.root -m 125.0 --expectSignal=1 -P MH --floatOtherPOIs=1 -t -1 --X-rtd TMCSO_PseudoAsimov=100 --X-rtd  TMCSO_AdaptivePseudoAsimov=0 --saveWorkspace --saveToys --algo=singles --cl=0.68 --robustFit 1 --stepSize 0.01 --minimizerTolerance 0.01 -s 12345 -v 9 > ${curdir}/${dir}.log 2>&1 

#combine -n ${dir} -M MultiDimFit FloatMass_comb_hzz2D_${dir}.root -m 125.0 --expectSignal=1 -P MH --floatOtherPOIs=1 -t -1 --saveWorkspace --saveToys --algo=singles --cl=0.68 --robustFit 1 --stepSize 0.005 --minimizerTolerance 0.005 -s 12345 -v 9 > ${curdir}/${dir}.log 2>&1 &

cd -

done

