#!/bin/bash

function compressPdf_bash {

    #    -dPDFSETTINGS=/screen lower quality, smaller size. (72 dpi)
    #    -dPDFSETTINGS=/ebook for better quality, but slightly larger pdfs. (150 dpi)
    #    -dPDFSETTINGS=/prepress output similar to Acrobat Distiller "Prepress Optimized" setting (300 dpi)
    #    -dPDFSETTINGS=/printer selects output similar to the Acrobat Distiller "Print Optimized" setting (300 dpi)
    #    -dPDFSETTINGS=/default selects output intended to be useful across a wide variety of uses, possibly at the expense of a larger output file

    echo "$1 : $2"
    output=$2"_$1.pdf"
    gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/$1 -dNOPAUSE -dQUIET -dBATCH -sOutputFile=$output $2

}

function mergePdf {
    #gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=charge.pdf pmt_cam_ev0.pdf pmt_cam_ev1.pdf pmt_cam_ev2.pdf pmt_cam_ev3.pdf pmt_cam_ev4.pdf pmt_cam_ev5.pdf pmt_cam_ev6.pdf pmt_cam_ev7.pdf pmt_cam_ev8.pdf pmt_cam_ev9.pdf pmt_cam_ev10.pdf pmt_cam_ev11.pdf pmt_cam_ev12.pdf pmt_cam_ev13.pdf pmt_cam_ev14.pdf pmt_cam_ev15.pdf pmt_cam_ev16.pdf pmt_cam_ev17.pdf pmt_cam_ev18.pdf pmt_cam_ev19.pdf pmt_cam_ev20.pdf pmt_cam_ev21.pdf pmt_cam_ev22.pdf pmt_cam_ev23.pdf pmt_cam_ev24.pdf pmt_cam_ev25.pdf pmt_cam_ev26.pdf pmt_cam_ev27.pdf pmt_cam_ev28.pdf pmt_cam_ev29.pdf pmt_cam_ev30.pdf pmt_cam_ev31.pdf pmt_cam_ev32.pdf pmt_cam_ev33.pdf pmt_cam_ev34.pdf pmt_cam_ev35.pdf pmt_cam_ev36.pdf pmt_cam_ev37.pdf pmt_cam_ev38.pdf pmt_cam_ev39.pdf pmt_cam_ev40.pdf pmt_cam_ev41.pdf pmt_cam_ev42.pdf pmt_cam_ev43.pdf pmt_cam_ev44.pdf pmt_cam_ev45.pdf pmt_cam_ev46.pdf pmt_cam_ev47.pdf pmt_cam_ev48.pdf pmt_cam_ev49.pdf pmt_cam_ev50.pdf pmt_cam_ev51.pdf pmt_cam_ev52.pdf pmt_cam_ev53.pdf pmt_cam_ev54.pdf pmt_cam_ev55.pdf pmt_cam_ev56.pdf pmt_cam_ev57.pdf pmt_cam_ev58.pdf pmt_cam_ev59.pdf pmt_cam_ev60.pdf pmt_cam_ev61.pdf pmt_cam_ev62.pdf pmt_cam_ev63.pdf pmt_cam_ev64.pdf pmt_cam_ev65.pdf pmt_cam_ev66.pdf pmt_cam_ev67.pdf pmt_cam_ev68.pdf pmt_cam_ev69.pdf pmt_cam_ev70.pdf pmt_cam_ev71.pdf pmt_cam_ev72.pdf pmt_cam_ev73.pdf pmt_cam_ev74.pdf pmt_cam_ev75.pdf pmt_cam_ev76.pdf pmt_cam_ev77.pdf pmt_cam_ev78.pdf pmt_cam_ev79.pdf pmt_cam_ev80.pdf pmt_cam_ev81.pdf pmt_cam_ev82.pdf pmt_cam_ev83.pdf pmt_cam_ev84.pdf pmt_cam_ev85.pdf pmt_cam_ev86.pdf pmt_cam_ev87.pdf pmt_cam_ev88.pdf pmt_cam_ev89.pdf pmt_cam_ev90.pdf pmt_cam_ev91.pdf pmt_cam_ev92.pdf pmt_cam_ev93.pdf pmt_cam_ev94.pdf pmt_cam_ev95.pdf pmt_cam_ev96.pdf pmt_cam_ev97.pdf pmt_cam_ev98.pdf pmt_cam_ev99.pdf
    #gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=time.pdf pmt_cam_ev0.pdf pmt_cam_ev1.pdf pmt_cam_ev2.pdf pmt_cam_ev3.pdf pmt_cam_ev4.pdf pmt_cam_ev5.pdf pmt_cam_ev6.pdf pmt_cam_ev7.pdf pmt_cam_ev8.pdf pmt_cam_ev9.pdf pmt_cam_ev10.pdf pmt_cam_ev11.pdf pmt_cam_ev12.pdf pmt_cam_ev13.pdf pmt_cam_ev14.pdf pmt_cam_ev15.pdf pmt_cam_ev16.pdf pmt_cam_ev17.pdf pmt_cam_ev18.pdf pmt_cam_ev19.pdf pmt_cam_ev20.pdf pmt_cam_ev21.pdf pmt_cam_ev22.pdf pmt_cam_ev23.pdf pmt_cam_ev24.pdf pmt_cam_ev25.pdf pmt_cam_ev26.pdf pmt_cam_ev27.pdf pmt_cam_ev28.pdf pmt_cam_ev29.pdf pmt_cam_ev30.pdf pmt_cam_ev31.pdf pmt_cam_ev32.pdf pmt_cam_ev33.pdf pmt_cam_ev34.pdf pmt_cam_ev35.pdf pmt_cam_ev36.pdf pmt_cam_ev37.pdf pmt_cam_ev38.pdf pmt_cam_ev39.pdf pmt_cam_ev40.pdf pmt_cam_ev41.pdf pmt_cam_ev42.pdf pmt_cam_ev43.pdf pmt_cam_ev44.pdf pmt_cam_ev45.pdf pmt_cam_ev46.pdf pmt_cam_ev47.pdf pmt_cam_ev48.pdf pmt_cam_ev49.pdf pmt_cam_ev50.pdf pmt_cam_ev51.pdf pmt_cam_ev52.pdf pmt_cam_ev53.pdf pmt_cam_ev54.pdf pmt_cam_ev55.pdf pmt_cam_ev56.pdf pmt_cam_ev57.pdf pmt_cam_ev58.pdf pmt_cam_ev59.pdf pmt_cam_ev60.pdf pmt_cam_ev61.pdf pmt_cam_ev62.pdf pmt_cam_ev63.pdf pmt_cam_ev64.pdf pmt_cam_ev65.pdf pmt_cam_ev66.pdf pmt_cam_ev67.pdf pmt_cam_ev68.pdf pmt_cam_ev69.pdf pmt_cam_ev70.pdf pmt_cam_ev71.pdf pmt_cam_ev72.pdf pmt_cam_ev73.pdf pmt_cam_ev74.pdf pmt_cam_ev75.pdf pmt_cam_ev76.pdf pmt_cam_ev77.pdf pmt_cam_ev78.pdf pmt_cam_ev79.pdf pmt_cam_ev80.pdf pmt_cam_ev81.pdf pmt_cam_ev82.pdf pmt_cam_ev83.pdf pmt_cam_ev84.pdf pmt_cam_ev85.pdf pmt_cam_ev86.pdf pmt_cam_ev87.pdf pmt_cam_ev88.pdf pmt_cam_ev89.pdf pmt_cam_ev90.pdf pmt_cam_ev91.pdf pmt_cam_ev92.pdf pmt_cam_ev93.pdf pmt_cam_ev94.pdf pmt_cam_ev95.pdf pmt_cam_ev96.pdf pmt_cam_ev97.pdf pmt_cam_ev98.pdf pmt_cam_ev99.pdf
    #gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=mask.pdf pmt_cam_ev0.pdf pmt_cam_ev1.pdf pmt_cam_ev2.pdf pmt_cam_ev3.pdf pmt_cam_ev4.pdf pmt_cam_ev5.pdf pmt_cam_ev6.pdf pmt_cam_ev7.pdf pmt_cam_ev8.pdf pmt_cam_ev9.pdf pmt_cam_ev10.pdf pmt_cam_ev11.pdf pmt_cam_ev12.pdf pmt_cam_ev13.pdf pmt_cam_ev14.pdf pmt_cam_ev15.pdf pmt_cam_ev16.pdf pmt_cam_ev17.pdf pmt_cam_ev18.pdf pmt_cam_ev19.pdf pmt_cam_ev20.pdf pmt_cam_ev21.pdf pmt_cam_ev22.pdf pmt_cam_ev23.pdf pmt_cam_ev24.pdf pmt_cam_ev25.pdf pmt_cam_ev26.pdf pmt_cam_ev27.pdf pmt_cam_ev28.pdf pmt_cam_ev29.pdf pmt_cam_ev30.pdf pmt_cam_ev31.pdf pmt_cam_ev32.pdf pmt_cam_ev33.pdf pmt_cam_ev34.pdf pmt_cam_ev35.pdf pmt_cam_ev36.pdf pmt_cam_ev37.pdf pmt_cam_ev38.pdf pmt_cam_ev39.pdf pmt_cam_ev40.pdf pmt_cam_ev41.pdf pmt_cam_ev42.pdf pmt_cam_ev43.pdf pmt_cam_ev44.pdf pmt_cam_ev45.pdf pmt_cam_ev46.pdf pmt_cam_ev47.pdf pmt_cam_ev48.pdf pmt_cam_ev49.pdf pmt_cam_ev50.pdf pmt_cam_ev51.pdf pmt_cam_ev52.pdf pmt_cam_ev53.pdf pmt_cam_ev54.pdf pmt_cam_ev55.pdf pmt_cam_ev56.pdf pmt_cam_ev57.pdf pmt_cam_ev58.pdf pmt_cam_ev59.pdf pmt_cam_ev60.pdf pmt_cam_ev61.pdf pmt_cam_ev62.pdf pmt_cam_ev63.pdf pmt_cam_ev64.pdf pmt_cam_ev65.pdf pmt_cam_ev66.pdf pmt_cam_ev67.pdf pmt_cam_ev68.pdf pmt_cam_ev69.pdf pmt_cam_ev70.pdf pmt_cam_ev71.pdf pmt_cam_ev72.pdf pmt_cam_ev73.pdf pmt_cam_ev74.pdf pmt_cam_ev75.pdf pmt_cam_ev76.pdf pmt_cam_ev77.pdf pmt_cam_ev78.pdf pmt_cam_ev79.pdf pmt_cam_ev80.pdf pmt_cam_ev81.pdf pmt_cam_ev82.pdf pmt_cam_ev83.pdf pmt_cam_ev84.pdf pmt_cam_ev85.pdf pmt_cam_ev86.pdf pmt_cam_ev87.pdf pmt_cam_ev88.pdf pmt_cam_ev89.pdf pmt_cam_ev90.pdf pmt_cam_ev91.pdf pmt_cam_ev92.pdf pmt_cam_ev93.pdf pmt_cam_ev94.pdf pmt_cam_ev95.pdf pmt_cam_ev96.pdf pmt_cam_ev97.pdf pmt_cam_ev98.pdf pmt_cam_ev99.pdf    
}

function printHelp { 
 
    echo " --> ERROR in input arguments <-- "
    echo " [0] -l  : Lower quality, smaller size (72 dpi)."
    echo " [0] -b  : Better quality, but slightly larger pdfs (150 dpi)."
    echo " [0] -p  : Output similar to Acrobat Distiller -Prepress Optimized- setting (300 dpi)."
    echo " [0] -o  : Output similar to Acrobat Distiller -Print Optimized- setting (300 dpi)."
    echo " [0] -d  : Output intended to be useful across a wide variety of uses, possibly at the expense of a larger output file."
    echo " [0] -a  : All."
    echo " [0] -m  : merge"    
    echo " [1]     : Input file."

    return 1

}

if [ $# -eq 0 ]
then   
    printHelp

elif [ $# -eq 1 ]
then
    printHelp     
else
    if [ "$1" = "-l" ]
    then
	compressPdf_bash screen $2
    elif [ "$1" = "-b" ]
    then
	compressPdf_bash ebook $2
    elif [ "$1" = "-p" ]
    then
	compressPdf_bash prepress $2
    elif [ "$1" = "-o" ]
    then
	compressPdf_bash printer $2
    elif [ "$1" = "-d" ]
    then
	compressPdf_bash default $2
    elif [ "$1" = "-a" ]
    then
	compressPdf_bash screen $2
	compressPdf_bash ebook $2
	compressPdf_bash prepress $2
	compressPdf_bash printer $2
	compressPdf_bash default $2
    elif [ "$1" = "-m" ]
    then
	mergePdf
    else	
	printHelp 
    fi
fi
