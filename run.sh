#make all
./lem-in < ${1:-"checker/good_maps/good_map04"} > _visualizer/lines.txt
cd _visualizer/c
echo "<!> compiling json list generator"
gcc list_jsonifier.c -o list_jsonifier.exe
cd ../..
cd _visualizer/c
echo "<!> building json from output ..."
./list_jsonifier.exe "lines" "$(cat ../lines.txt)" "1" > ../lines.json
cd ..
echo "<!> injecting json data to html hidden container"
sed '/<p id="lines">/ r lines.json' html/index_tpl.html > html/index.html

open html/index.html
#xdg-open html/index.html
#awk 'FNR==NR{n=n ORS $0; next} /<integers>/{$0=$0 n} 1' output.txt index.html