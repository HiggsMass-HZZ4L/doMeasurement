

cd CMSSW_7_1_5/src/

eval `scram r -sh`

cd -

sh buildPackage.sh

rm -rf cards_sm13_2D*

echo "reco 2D"
python makeDCsandWSs.py -i SM_inputs_13TeV -a sm13_2D_reco_2p7fb_CB -b -d 1 -e 0 -j 0
echo "reco 2D ebe"
python makeDCsandWSs.py -i SM_inputs_13TeV -a sm13_2Debe_reco_2p7fb_CB -b -d 1 -e 1 -j 0

echo "refit 2D"
python makeDCsandWSs.py -i SM_inputs_13TeV_refit -a sm13_2D_refit_2p7fb_CB -b -d 1 -e 0 -j 0 -r 1
echo "refit 2D ebe"
python makeDCsandWSs.py -i SM_inputs_13TeV_refit -a sm13_2Debe_refit_2p7fb_CB -b -d 1 -e 1 -j 0 -r 1

