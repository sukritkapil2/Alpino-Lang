//this is a comment
//input alpino program

//function
fun addFive(x) {
    var z = x+5;
    x+++;
    return z;
}

//sequential statements
var x = -5;
var y = 10;

y = x;

print(x);
z = input('Enter a number');

x = addFive(x);

print(x);

//conditional statement
if(x == 10) {
    print("Success!");
} elif {
    print("Failure!");
}

//loop statement
loop(i = 1;i <= 10; i++) {
    print(i);
    if(i == 6) {
        break;
    } elif {
        continue;
    }
}

//array
var arr[10] = {1, 2, 4, 7};