

main(){
    IOS();
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // Basically the same as rand()
    vector<int> v(10); iota(ALL(v),1);
    shuffle(ALL(v), rng); // Use instead of random_shuffle
    for (int x : v) cout<<x<<' ';
    cout<<"Random number [0,100): "<<rng()%100<<endl;
} 
