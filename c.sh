if gcc c.cpp -lstdc++ -std=c++17 -o ./c 2>&1 > c.complog
then
	./c | tee -a c.log | more
else
	more c.complog
fi

