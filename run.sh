wget -i paths.txt -c -P test_images  
find test_images  -type f -name "*.jpg" -exec ls -al {} \; | sort -k 5 -n | sed 's/ \+/\t/g' | cut -f 9  > data.txt
rm input_images/* output_images/* quatrees_images/*
g++ -std=c++17 main.cpp -L/usr/X11R6/lib -lm -lpthread -lX11
./a.out