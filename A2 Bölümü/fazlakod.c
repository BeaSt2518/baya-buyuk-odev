    while(i != 0){
        if(checkBalance(btree, i) > 1){
            if(key < btree[2*i + 1]){
                swap(&btree[i], &btree[2*i + 1]);
                i = 2*i + 1;
            }
            else{
                swap(&btree[i], &btree[2*i + 2]);
                i = 2*i + 2;
            }
        }
        else if(checkBalance(btree, i) < -1){
            if(key > btree[2*i + 2]){
                swap(&btree[i], &btree[2*i + 2]);
                i = 2*i + 2;
            }
            else{
                swap(&btree[i], &btree[2*i + 1]);
                i = 2*i + 1;
            }
        }
        else{
            break;
        }
    }

        while(i != 0){
        if(checkBalance(btree, i) > 1){
            if(key < btree[2*i + 1]){
                swap(&btree[i], &btree[2*i + 1]);
                i = 2*i + 1;
            }
            else{
                swap(&btree[i], &btree[2*i + 2]);
                i = 2*i + 2;
            }
        }
        else if(checkBalance(btree, i) < -1){
            if(key > btree[2*i + 2]){
                swap(&btree[i], &btree[2*i + 2]);
                i = 2*i + 2;
            }
            else{
                swap(&btree[i], &btree[2*i + 1]);
                i = 2*i + 1;
            }
        }
        else{
            break;
        }
    }

    void insertBalanced(int btree[], int key){
    int i = 0;
    while(btree[i] != NULLVALUE){
        if(key < btree[i]){
            i = 2*i + 1;
        }
        else{
            i = 2*i + 2;
        }
    }
    btree[i] = key;
        while(i != 0){
        if(checkBalance(btree, i) > 1){
            if(key < btree[2*i + 1]){
                swap(&btree[i], &btree[2*i + 1]);
                i = 2*i + 1;
            }
            else{
                swap(&btree[i], &btree[2*i + 2]);
                i = 2*i + 2;
            }
        }
        else if(checkBalance(btree, i) < -1){
            if(key > btree[2*i + 2]){
                swap(&btree[i], &btree[2*i + 2]);
                i = 2*i + 2;
            }
            else{
                swap(&btree[i], &btree[2*i + 1]);
                i = 2*i + 1;
            }
        }
        else{
            break;
        }
    }


}

void insertBalanced(int btree[], int key){
    int i = 0;
    while(btree[i] != NULLVALUE){
        if(key < btree[i]){
            i = 2*i + 1;
        }
        else{
            i = 2*i + 2;
        }
    }
    btree[i] = key;
    while(i != 0){
        if(checkBalance(btree, i) > 1){
            if(key < btree[2*i + 1]){
                rightRotate(btree, i);
            }
            else{
                leftRotate(btree, 2*i + 1);
                rightRotate(btree, i);
            }
        }
        else if(checkBalance(btree, i) < -1){
            if(key > btree[2*i + 2]){
                leftRotate(btree, i);
            }
            else{
                rightRotate(btree, 2*i + 2);
                leftRotate(btree, i);
            }
        }
        i = (i-1)/2;
    }


}