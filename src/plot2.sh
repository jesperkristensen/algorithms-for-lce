
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

rm results/*.pdf

datafile="results/length-rand10.txt"
listdata

yavg="set logscale y\nset yrange [7e-9:1e-6]\nset title 'Average case strings'"
ywc="set logscale y\nset yrange [7e-9:1e-5]\nset title 'Worst case strings'"
ymc="set logscale y\nset yrange [7e-9:1e-5]\nset title 'Medium LCE-size strings'"

style="lines"

# x-axis = LCE value
xtra="unset logscale x\nset yrange [1e-8:1e-7]\nset xrange [0:10]\nset title 'Average case strings, alphabet = 4'"
datafile="results/value-rand4.txt"
plotfile="results/value-article-rand4.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra="unset logscale x\nset yrange [1e-8:1e-7]\nset xrange [0:1000]\nset title 'Worst case strings'"
datafile="results/value-alla.txt"
plotfile="results/value-article-alla.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra="unset logscale x\nset yrange [1e-8:1e-7]\nset xrange [0:1000]\nset title 'String of 10 characters repeated 100 times'"
datafile="results/value-repeat10-10.txt"
plotfile="results/value-article-repeat10-10.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

style="linespoints"

# Overall Fingerprint
xtra=$yavg
datafile="results/length-rand10.txt"
plotfile="results/length-article-rand10.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra=$ywc
datafile="results/length-alla.txt"
plotfile="results/length-article-alla.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra=$ymc
datafile="results/length-repeat5.txt"
plotfile="results/length-article-repeat5.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra=$ymc
datafile="results/length-repeat25.txt"
plotfile="results/length-article-repeat25.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra=$ymc
datafile="results/length-repeat50.txt"
plotfile="results/length-article-repeat50.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra=$ymc
datafile="results/length-repeat100.txt"
plotfile="results/length-article-repeat100.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra=$ymc
datafile="results/length-repeat-pow.txt"
plotfile="results/length-article-repeat-pow.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra=$ymc
datafile="results/length-repeat-sqrt.txt"
plotfile="results/length-article-repeat-sqrt.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

#Overall Fingerprint Slides
slides="\nunset title\nunset xlabel\nunset ylabel\nunset key"
xtra="$yavg$slides"
datafile="results/length-rand10.txt"
plotfile="results/length-slides-rand10.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra="$ywc$slides"
datafile="results/length-alla.txt"
plotfile="results/length-slides-alla.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

xtra="$ymc$slides"
datafile="results/length-repeat-pow.txt"
plotfile="results/length-slides-repeat-pow.plt"
oneplot "DirectComp," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "RMQ<n;1>,"

# Not used
#xtra=$yavg
#datafile="results/length-rand10.txt"
#plotfile="results/length-main-rand10.plt"
#oneplot "DirectComp," "DirectLookup," "DirectCompLookup<10>," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>wc," "Fingerprint_3<n^{2/3};n^{1/3}>ac<1;1>," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}wc," "Fingerprint_{log n}ac," "RMQ<1;n>," "RMQ<n;1>," "DirectComp<1>RMQ<n;1>,"

#xtra=$ywc
#datafile="results/length-alla.txt"
#plotfile="results/length-main-alla.plt"
#oneplot "DirectComp," "DirectLookup," "DirectCompLookup<10>," "Fingerprint_2<sqrt n>ac," "Fingerprint_3<n^{2/3};n^{1/3}>wc," "Fingerprint_3<n^{2/3};n^{1/3}>ac<1;1>," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}wc," "Fingerprint_{log n}ac," "RMQ<1;n>," "RMQ<n;1>," "DirectComp<1>RMQ<n;1>,"

# DirectCompLookup

xtra="$yavg\nset xrange [10:100000]"
datafile="results/length-rand10.txt"
plotfile="results/length-complookup-rand10.plt"
oneplot "DirectComp," "DirectCompLookup<n/log n>," "DirectCompLookup<sqrt n>," "DirectCompLookup<log n>," "DirectLookup," "RMQ<n;1>,"

xtra="$ywc\nset xrange [10:100000]"
datafile="results/length-alla.txt"
plotfile="results/length-complookup-alla.plt"
oneplot "DirectComp," "DirectCompLookup<n/log n>," "DirectCompLookup<sqrt n>," "DirectCompLookup<log n>," "DirectLookup," "RMQ<n;1>,"

# Fingerprint_2 variants downward (normal) cutoff
xtra=$yavg
datafile="results/length-rand10.txt"
plotfile="results/length-fingerprint-2l-rand10.plt"
oneplot "Fingerprint_2<1/2sqrt n>ac," "Fingerprint_2<1/4sqrt n>ac," "Fingerprint_2<sqrt n>ac," "Fingerprint_2<2sqrt n>ac," "Fingerprint_2<4sqrt n>ac," "Fingerprint_2<8sqrt n>ac," "Fingerprint_2<16sqrt n>ac,"

xtra=$ywc
datafile="results/length-alla.txt"
plotfile="results/length-fingerprint-2l-alla.plt"
oneplot "Fingerprint_2<1/2sqrt n>ac," "Fingerprint_2<1/4sqrt n>ac," "Fingerprint_2<sqrt n>ac," "Fingerprint_2<2sqrt n>ac," "Fingerprint_2<4sqrt n>ac," "Fingerprint_2<8sqrt n>ac," "Fingerprint_2<16sqrt n>ac,"

# Fingerprint_2 variants cache optimizations
xtra=$yavg
datafile="results/length-rand10.txt"
plotfile="results/length-fingerprint-cache-rand10.plt"
oneplot "Fingerprint_2<sqrt n>ac," "Fingerprint_2<sqrt n>ac_{cache-horizontal-shift}," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult},"

xtra="$yavg\nset title 'Average case strings, alphabet size 2'"
datafile="results/length-rand2.txt"
plotfile="results/length-fingerprint-cache-rand2.plt"
oneplot "Fingerprint_2<sqrt n>ac," "Fingerprint_2<sqrt n>ac_{cache-horizontal-shift}," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult},"

xtra=$ywc
datafile="results/length-alla.txt"
plotfile="results/length-fingerprint-cache-alla.plt"
oneplot "Fingerprint_2<sqrt n>ac," "Fingerprint_2<sqrt n>ac_{cache-horizontal-shift}," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult},"

xtra=$ymc
datafile="results/length-repeat-pow.txt"
plotfile="results/length-fingerprint-cache-repeat-pow.plt"
oneplot "Fingerprint_2<sqrt n>ac," "Fingerprint_2<sqrt n>ac_{cache-horizontal-shift}," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult},"

# Fingerprint_{log n} variants cache optimizations
xtra=$yavg
datafile="results/length-rand10.txt"
plotfile="results/length-fingerprint-log-cache-rand10.plt"
oneplot "Fingerprint_{log n}ac," "Fingerprint_{log n}ac_{cache-vertical-mult},"

xtra=$ywc
datafile="results/length-alla.txt"
plotfile="results/length-fingerprint-log-cache-alla.plt"
oneplot "Fingerprint_{log n}ac," "Fingerprint_{log n}ac_{cache-vertical-mult},"

# Fingerprint_{log n} variants upward (average case) cutoff
xtra=$yavg
datafile="results/length-rand10.txt"
plotfile="results/length-fingerprint-avglog-rand10.plt"
oneplot "Fingerprint_{log n}wc," "Fingerprint_{log n}ac,"

xtra=$ywc
datafile="results/length-alla.txt"
plotfile="results/length-fingerprint-avglog-alla.plt"
oneplot "Fingerprint_{log n}wc," "Fingerprint_{log n}ac,"

# Fingerprint_3 variants upward (average case) cutoff
xtra=$yavg
datafile="results/length-rand10.txt"
plotfile="results/length-fingerprint-avg3l-rand10.plt"
oneplot "Fingerprint_3<n^{2/3};n^{1/3}>wc," "Fingerprint_3<n^{2/3};n^{1/3}>ac<n^{1/3};n^{2/3}>," "Fingerprint_3<n^{2/3};n^{1/3}>ac,"

xtra=$ywc
datafile="results/length-alla.txt"
plotfile="results/length-fingerprint-avg3l-alla.plt"
oneplot "Fingerprint_3<n^{2/3};n^{1/3}>wc," "Fingerprint_3<n^{2/3};n^{1/3}>ac<n^{1/3};n^{2/3}>," "Fingerprint_3<n^{2/3};n^{1/3}>ac,"

# RMQ variants
xtra=$yavg
datafile="results/length-rand10.txt"
plotfile="results/length-rmq-rand10.plt"
oneplot "RMQ<1;n>_{virtual}," "RMQ<n;1>_{virtual}," "RMQ<n;2log n>_{virtual}," "RMQ<n;4log n>_{virtual}," #"RMQ<succinct;?>_{virtual}," "RMQ<optimal>_{virtual},"

xtra=$ywc
datafile="results/length-alla.txt"
plotfile="results/length-rmq-alla.plt"
oneplot "RMQ<1;n>_{virtual}," "RMQ<n;1>_{virtual}," "RMQ<n;2log n>_{virtual}," "RMQ<n;4log n>_{virtual}," #"RMQ<succinct;?>_{virtual}," "RMQ<optimal>_{virtual},"

# RMQ vs. DirectComp vs. combination
xtra=$yavg
datafile="results/length-rand10.txt"
plotfile="results/length-rmq-directcomp-rand10.plt"
oneplot "DirectComp," "RMQ<n;1>," "DirectComp<1>RMQ<n;1>,"

xtra=$ywc
datafile="results/length-alla.txt"
plotfile="results/length-rmq-directcomp-alla.plt"
oneplot "DirectComp," "RMQ<n;1>," "DirectComp<1>RMQ<n;1>,"

# RMQ vs. DirectComp
xtra="$yavg\nunset title\nunset xlabel\nunset ylabel\nunset key"
datafile="results/length-rand10.txt"
plotfile="results/length-rmq-directcomp-slide-rand10.plt"
oneplot "DirectComp," "RMQ<n;1>,"

xtra="$ywc\nunset title\nunset xlabel\nunset ylabel\nunset key"
datafile="results/length-alla.txt"
plotfile="results/length-rmq-directcomp-slide-alla.plt"
oneplot "DirectComp," "RMQ<n;1>,"

# space
xtra="set logscale y\nset yrange [2:3e14]"
datafile="results/space.txt"
plotfile="results/space.plt"
oneplot "DirectComp," "DirectLookup," "DirectCompLookup<n/log n>," "DirectCompLookup<sqrt n>," "DirectCompLookup<log n>," "Fingerprint_2<sqrt n>ac," "Fingerprint_2<sqrt n>ac_{cache-horizontal-shift}," "Fingerprint_2<sqrt n>ac_{cache-horizontal-mult}," "Fingerprint_3<n^{2/3};n^{1/3}>ac," "Fingerprint_{log n}ac," "Fingerprint_{log n}ac_{cache-vertical-mult}," "RMQ<1;n>," "RMQ<n;1>," "DirectComp<1>RMQ<n;1>,"

rm results/*.plt
rm results/*.eps
