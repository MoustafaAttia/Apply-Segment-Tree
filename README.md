# Apply Segment Tree

In this repository I applied the code of Segment Tree data structure from: [https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/] 
to use it in any problem that requires segment tree like sum in range problem or RMQ (range minimum query) problem.
I added some minor changes on above code: 
- Make alias type name to make it global for use in any numeric data type (e.g. int, float, double, ... etc.)
- Add isvalid parameter in getSum and updateValue method to check whether or not method return correct answer, also to distinguish
 between return -1 in case of invalid query or in case where -1 is the correct answer
- Replace passing pointer-to-array to vector

Also method InitializeVector is just to initialize random numbers, it's just for testing and can be removed.
