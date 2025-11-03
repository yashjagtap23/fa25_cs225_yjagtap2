/* Your code here! */
//ii need default constructor 
// created empy private vector 
DisjointSets::DisjointSets() {
    myVec = {};
}

DisjointSets::DisjointSets(int num) {
    myVec = std::vector<int>{num, -1};
}


void DisjointSets::addElements(int num) {
    for (int i = 0; i < num; i++) {
        myVec.push_back(-1);
    }
}
//add ele 
// index 0->nimp-1 
//for loop 1 ->num
//push back
//ele as root size -1
//add to priv vector

//find 
// return root of set w elem 
//go thru tree and paternt pointer of every node tofinal rot
//recusrscion

int DisjointSets::find(int elem) {
    if (myVec[elem] < 0) {
        return elem; //root
    }
    else {
        //compression thin we learns in lectue
        myVec[elem] = find(myVec[elem]);
        return myVec[elem];
    }
}
//unites set union by size 
//smaler set is child root of larger
// use find to get roots, if in same set nothing
// else get size, find bigger,, combined root

// find the rep of the group and use it to check if they are in the same groups
// use find 

//set root of one tree to be child of the other 

//root = find(a)
if root equal then return same set 

if size(a) > sizeb:
size b parent is size a
else vice bersa

void DisjointSets::setUnion(int a, int b) {
    int r1 = find(a);
    int r2 = find(b);

    if (r1 == r2){
        return;
    }
    int sizeR1 = myVec[r1];
    int sizeR2 = myVec[r2];

    if (sizeR1 > sizeR2) {
        myVec[r2] = r1;
        myVec[r1] = sizeR1 + sizeR2;
    } else {
        myVec[r1] = r2;
        myVec[r2] = sizeR1 + sizeR2;
    }
}
    
int DisjointSets::size(int elem) {
    int root1 = find(elem);
    return (myVec[root1] * -1);
}