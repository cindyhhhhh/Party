# ADA-Party

Problem Description:

YP, BB, and their K classmates are going to the ADA party. To enjoy the party, they prepared N bags of candies, where the i-th bag contains ai candies.
Now it’s party time! These (K + 2) people decide to have fun together, so they play a game that involves eating candies. In this game, they select two integers l, r and eat all the candies in the l-th bag, (l + 1)-th bag, . . ., and the r-th bag (not necessarily in order) together based on the following rules: first, YP picks a bag with the maximal number of candies and eats every candy in it. Then BB picks a bag with the minimal number of candies and also eats the candies in it. After YP and BB finish the candies in those two bags, the other K people hope that they can eat the same number of candies in the remaining (r − l − 1) bags. It is okay that they don’t eat any candies.
YP and BB think that (l, r) is a good pair if the following conditions hold: •1≤l<r≤n
• The remaining K people can eat the same number of candies. Note that the candies in a bag can be split among multiple people, and each person can eat candies from multiple bags.
Please help YP and BB calculate the number of good pairs.


Input:

The first line of the input contains two integers N and K, denoting the number of bags and the number of YP and BB’s classmates respectively.
The second line of the input contains N space-separated integers a1, a2, . . . , aN , where the i-th integer denotes that the i-th bag contains ai candies.
