Node n1 = {1, NULL, NULL};
Node n2 = {4, NULL, NULL};
Node n3 = {'*', &n1, &n2};
Node n4 = {16, NULL, NULL};
Node n5 = {25, NULL, NULL};
Node n6 = {'+', &n4, &n5};
Node n7 = {'+', &n3, &n6};
Node *exp = &n7;
