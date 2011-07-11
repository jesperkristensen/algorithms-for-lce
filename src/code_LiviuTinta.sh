cd manzini_ds/
make da_ssort.a 
cp ds_ssort.a ../ds_ssort.a
make bwtlcp.a
cp bwtlcp.a ../bwtlcp.a
cd ..
cd RMQ_n_logn/
make RMQ.a
cp RMQ.a ../RMQ.a
cd ..
cd qsufsort/
make qsufsort.a
cp qsufsort.a ../qsufsort.a
cd ..
cd compute_avg_lcp
make compute_avg_lcp.a
cp compute_avg_lcp.a ../compute_avg_lcp.a
cd ..
cd SA_Bentley\&Sedgewick/
make SABentleySedgewick.a
cp SABentleySedgewick.a ../SABentleySedgewick.a
cd ..
make
