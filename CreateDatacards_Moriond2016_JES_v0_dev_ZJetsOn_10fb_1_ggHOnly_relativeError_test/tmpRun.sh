curdir=`pwd`

for dir in sm13_1D_reco sm13_1D_refit sm13_1Debe_reco sm13_1Debe_refit #sm13_2D_reco sm13_2D_refit sm13_2Debe_reco sm13_2Debe_refit

do

cd cards_${dir}_2p7fb_CB/HCG/125
combineCards.py hzz4l_13TeV_4mu=hzz4l_4muS_13TeV.txt hzz4l_13TeV_4e=hzz4l_4eS_13TeV.txt hzz4l_13TeV_2e2mu=hzz4l_2e2muS_13TeV.txt  > hzz4l_allS_13TeV.txt
pwd
ls
#mkdir ${dirTag} ${dirTag}_4mu ${dirTag}_4e ${dirTag}_2e2mu

#text2workspace.py comb_${dir}.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:floatingHiggsMass   --PO higgsMassRange=115,135 --PO=muAsPOI -o ${dirTag}/FloatMass_comb_hzz2D_${dir}.root
#text2workspace.py hzz4l_4muS_13TeV.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:floatingHiggsMass   --PO higgsMassRange=115,135 --PO=muAsPOI -o ${dirTag}_4mu/FloatMass_comb_hzz2D_${dir}_4mu.root
#text2workspace.py hzz4l_4eS_13TeV.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:floatingHiggsMass   --PO higgsMassRange=115,135 --PO=muAsPOI -o ${dirTag}_4e/FloatMass_comb_hzz2D_${dir}_4e.root
#text2workspace.py hzz4l_2e2muS_13TeV.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:floatingHiggsMass   --PO higgsMassRange=115,135 --PO=muAsPOI -o ${dirTag}_2e2mu/FloatMass_comb_hzz2D_${dir}_2e2mu.root

#cd ${dirTag}
#combine -n ${dir} -M MultiDimFit FloatMass_comb_hzz2D_${dir}.root -m 125.0 -P MH --floatOtherPOIs=1 --expectSignal=1 -t -1 --X-rtd TMCSO_PseudoAsimov=1000 --X-rtd  TMCSO_AdaptivePseudoAsimov=0 --saveWorkspace --saveToys --robustFit 1 --stepSize 0.01 --minimizerTolerance 0.01 -s SEED --algo=singles --cl=0.68 -v 9 > ${curdir}/savedLog/${dirTag}/sm13_${dir}_TAG.log 2>&1 &

#cd ../${dirTag}_4mu
#combine -n ${dir} -M MultiDimFit FloatMass_comb_hzz2D_${dir}_4mu.root -m 125.0 -P MH --floatOtherPOIs=1 --expectSignal=1 -t -1 --X-rtd TMCSO_PseudoAsimov=1000 --X-rtd  TMCSO_AdaptivePseudoAsimov=0 --saveWorkspace --saveToys --robustFit 1 --stepSize 0.01 --minimizerTolerance 0.01 -s SEED --algo=singles --cl=0.68 -v 9 > ${curdir}/savedLog/${dirTag}/sm13_${dir}_4mu_TAG.log 2>&1 &

#cd ../${dirTag}_4e
#combine -n ${dir} -M MultiDimFit FloatMass_comb_hzz2D_${dir}_4e.root -m 125.0 -P MH --floatOtherPOIs=1 --expectSignal=1 -t -1 --X-rtd TMCSO_PseudoAsimov=1000 --X-rtd  TMCSO_AdaptivePseudoAsimov=0 --saveWorkspace --saveToys --robustFit 1 --stepSize 0.01 --minimizerTolerance 0.01 -s SEED --algo=singles --cl=0.68 -v 9 > ${curdir}/savedLog/${dirTag}/sm13_${dir}_4e_TAG.log 2>&1 &

#cd ../${dirTag}_2e2mu
#combine -n ${dir} -M MultiDimFit FloatMass_comb_hzz2D_${dir}_2e2mu.root -m 125.0 -P MH --floatOtherPOIs=1 --expectSignal=1 -t -1 --X-rtd TMCSO_PseudoAsimov=1000 --X-rtd  TMCSO_AdaptivePseudoAsimov=0 --saveWorkspace --saveToys --robustFit 1 --stepSize 0.01 --minimizerTolerance 0.01 -s SEED --algo=singles --cl=0.68 -v 9 > ${curdir}/savedLog/${dirTag}/sm13_${dir}_2e2mu_TAG.log 2>&1 &

cd $curdir
done

