echo "Running unit tests."

for i in tests/*_tests
do
	if test -f $i
	then
		TESTLIB="$i ./build/libex29.so"
		$TESTLIB print_a_message "Hi" 2
		$TESTLIB uppercase "hello world" 11
		$TESTLIB lowercase "HELLO there" 11
		$TESTLIB fail_on_purpose 5 
		$TESTLIB asdfsg asdfasgs 5
	fi
done

echo ""
