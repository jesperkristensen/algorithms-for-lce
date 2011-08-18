
oneplot()
{
    cat plotheader.txt > $plotfile
    echo "set out '$plotfile.eps'" >> $plotfile
    echo "set xrange [10:]" >> $plotfile
    title=$(head -1 $datafile | sed -e 's/,/\n/g' | head -1)
    # echo "set title '$title'" >> $plotfile
    echo -e "$xtra" >> $plotfile
    echo "plot \\" >> $plotfile
    first=1
    for algo in "$@"
    do
        if test $first = 0
        then
            echo ", \\" >> $plotfile
        fi
        first=0
        algoidx=$(head -1 $datafile | sed -e 's/,/,\n/g' | grep -nF "$algo" -m1 | cut -d':' -f1)
        echo -n "  '$datafile' using 1:$algoidx with $style" >> $plotfile
    done
    echo "Plotting $plotfile";
    gnuplot $plotfile; ps2pdf -dEPSCrop $plotfile.eps $plotfile.pdf
}

listdata()
{
    head -1 $datafile | sed -e 's/,/,\n/g'
    echo ""
}

yavg="set logscale y\nset yrange [7e-9:1e-6]\nset title 'Average case strings'"
ywc="set logscale y\nset yrange [7e-9:1e-5]\nset title 'Worst case strings'"
ymc="set logscale y\nset yrange [7e-9:1e-5]\nset title 'Medium LCE-size strings'"

style="linespoints"

#Overall Cache Fingerprint Slides

slides="\nunset title\nunset xlabel\nunset ylabel\nunset key"
xtra="$yavg$slides"
datafile="results/length-slides-rand10.txt"
plotfile="results/length-slides-cache-rand10.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult}," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra="$yavg$slides"
datafile="results/length-slides-rand2.txt"
plotfile="results/length-slides-cache-rand2.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult}," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra="$ywc$slides"
datafile="results/length-slides-alla.txt"
plotfile="results/length-slides-cache-alla.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult}," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra="$ymc$slides"
datafile="results/length-slides-repeat-pow.txt"
plotfile="results/length-slides-cache-repeat-pow.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult}," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

# fp2 cache

xtra="$yavg$slides"
datafile="results/length-slides-rand10.txt"
plotfile="results/length-slides-cache-fp2-rand10.plt"
oneplot "Fingerprint_2<sqrt n>ac," "Fingerprint_2<sqrt n>ac_{cache-horizontal-shift}," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult},"

xtra="$ywc$slides"
datafile="results/length-slides-alla.txt"
plotfile="results/length-slides-cache-fp2-alla.plt"
oneplot "Fingerprint_2<sqrt n>ac," "Fingerprint_2<sqrt n>ac_{cache-horizontal-shift}," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult},"

# fp3 cache

xtra="$yavg$slides"
datafile="results/length-slides-rand10.txt"
plotfile="results/length-slides-cache-fp3-rand10.plt"
oneplot "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac_{cache-horizontal-shift}," "Fingerprint_3<n^{2/3};n^{1/3}>ac_{cache-horizontal-mult},"

xtra="$ywc$slides"
datafile="results/length-slides-alla.txt"
plotfile="results/length-slides-cache-fp3-alla.plt"
oneplot "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac_{cache-horizontal-shift}," "Fingerprint_3<n^{2/3};n^{1/3}>ac_{cache-horizontal-mult},"

rm results/*.plt
rm results/*.eps
