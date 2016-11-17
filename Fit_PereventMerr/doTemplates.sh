createWSDIR=$1

./Template_Sig.exe 125 4mu REFIT
cp Dm_signal_REFIT_4mu.root ../${createWSDIR}/templates2D_refit/Dm_signal_4mu.root
#./Template_Sig.exe 125 4e REFIT
#cp Dm_signal_REFIT_4e.root ../${createWSDIR}/templates2D_refit/Dm_signal_4e.root
#./Template_Sig.exe 125 2e2mu+2mu2e REFIT
#cp Dm_signal_REFIT_2e2mu+2mu2e.root ../${createWSDIR}/templates2D_refit/Dm_signal_2e2mu.root


./Template_Sig.exe 125 4mu RECO
cp Dm_signal_RECO_4mu.root ../${createWSDIR}/templates2D/Dm_signal_4mu.root
#./Template_Sig.exe 125 4e RECO
#cp Dm_signal_RECO_4e.root ../${createWSDIR}/templates2D/Dm_signal_4e.root
#./Template_Sig.exe 125 2e2mu+2mu2e RECO
#cp Dm_signal_RECO_2e2mu+2mu2e.root ../${createWSDIR}/templates2D/Dm_signal_2e2mu.root
