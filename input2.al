fun fact(n) {
    if(n <= 1) {
        return 1;
    } elif {
        return n*fact(n-1);
    }
}

var x;
x = 1;
loop(x; x <= 10; x++) {
    print(x);
    print(fact(x));
    print("\n");
}