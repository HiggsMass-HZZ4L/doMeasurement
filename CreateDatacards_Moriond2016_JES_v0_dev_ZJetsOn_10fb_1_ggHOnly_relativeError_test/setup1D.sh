

cd CMSSW_7_1_5/src/

eval `scram r -sh`

cd -

sh buildPackage.sh

rm -rf cards_sm13_1D*

echo "reco 1D"
python makeDCsandWSs.py -i SM_inputs_13TeV -a sm13_1D_reco_2p7fb_CB -b -d 0 -e 0 -j 0
echo "reco 1D ebe"
python makeDCsandWSs.py -i SM_inputs_13TeV -a sm13_1Debe_reco_2p7fb_CB -b -d 0 -e 1 -j 0

echo "refit 1D"
python makeDCsandWSs.py -i SM_inputs_13TeV_refit -a sm13_1D_refit_2p7fb_CB -b -d 0 -e 0 -j 0 -r 1
echo "refit 1D ebe"
python makeDCsandWSs.py -i SM_inputs_13TeV_refit -a sm13_1Debe_refit_2p7fb_CB -b -d 0 -e 1 -j 0 -r 1

