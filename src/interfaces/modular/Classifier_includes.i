%{
 #include <shogun/machine/Machine.h>
 #include <shogun/classifier/svm/GNPPSVM.h>
 #include <shogun/classifier/svm/GPBTSVM.h>
 #include <shogun/machine/DistanceMachine.h>
 #include <shogun/classifier/LDA.h>
 #include <shogun/classifier/QDA.h>
 #include <shogun/classifier/svm/LibLinear.h>
 #include <shogun/classifier/svm/LibSVM.h>
 #include <shogun/classifier/svm/LibSVMOneClass.h>
 #include <shogun/machine/LinearMachine.h>
 #include <shogun/machine/OnlineLinearMachine.h>
 #include <shogun/classifier/LPBoost.h> 
 #include <shogun/classifier/LPM.h>
 #include <shogun/classifier/svm/MPDSVM.h>
 #include <shogun/classifier/svm/OnlineSVMSGD.h>
 #include <shogun/classifier/svm/OnlineLibLinear.h>
 #include <shogun/classifier/Perceptron.h>
 #include <shogun/classifier/AveragedPerceptron.h>
 #include <shogun/classifier/SubGradientLPM.h>
 #include <shogun/classifier/svm/SubGradientSVM.h>
 #include <shogun/classifier/svm/SVM.h>
 #include <shogun/classifier/svm/SVMLin.h>
 #include <shogun/classifier/GaussianNaiveBayes.h>
 #include <shogun/machine/KernelMachine.h>
 #include <shogun/classifier/svm/SVMOcas.h>
 #include <shogun/classifier/svm/SVMSGD.h>
 #include <shogun/classifier/svm/SGDQN.h>
 #include <shogun/classifier/svm/WDSVMOcas.h>
 #include <shogun/classifier/PluginEstimate.h> 
 #include <shogun/classifier/mkl/MKL.h>
 #include <shogun/classifier/mkl/MKLClassification.h>
 #include <shogun/classifier/mkl/MKLOneClass.h>
 #include <shogun/classifier/vw/VowpalWabbit.h>
 #include <shogun/classifier/svm/NewtonSVM.h>

#ifdef USE_SVMLIGHT
 #include <shogun/classifier/svm/SVMLight.h>
 #include <shogun/classifier/svm/SVMLightOneClass.h>
#endif //USE_SVMLIGHT
%}
