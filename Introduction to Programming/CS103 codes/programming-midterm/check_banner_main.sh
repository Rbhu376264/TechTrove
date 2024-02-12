#!/bin/bash

./banner_sol > sol.txt
./banner > stu.txt
diff sol.txt stu.txt &>/dev/null

if [ $? -ne 0 ]
then
  echo "Your main must output exactly 'No font file given.' when the font file command line argument is missing."
  exit 1
fi

./banner_sol bad.font > sol.txt
./banner bad.font > stu.txt
diff sol.txt stu.txt &>/dev/null

if [ $? -ne 0 ]
then
  echo "Your main must output exactly 'Unable to read font file.' when the font file can not be opened properly."
  exit 2
fi

./banner_sol big.font > sol.txt <<< "Hello 103L!"
./banner big.font > stu.txt <<< "Hello 103L!"
diff sol.txt stu.txt &>/dev/null

if [ $? -ne 0 ]
then
  echo "For the test message 'Hello 103L!' there was some difference in your output. Compare your output using ./banner and ./banner_sol"
  exit 3
fi

echo "banner main() passed."
