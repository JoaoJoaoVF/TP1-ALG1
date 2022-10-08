// C++ implementation to find if the given
// expression is satisfiable using the
// Kosaraju's Algorithm
#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;

// data structures used to implement Kosaraju's
// Algorithm. Please refer
// https://www.geeksforgeeks.org/strongly-connected-components/
vector<int> adj[MAX];
vector<int> adjInv[MAX];
bool visited[MAX];
bool visitedInv[MAX];
stack<int> s;

// this array will store the SCC that the
// particular node belongs to
int scc[MAX];

// counter maintains the number of the SCC
int counter = 1;

// adds edges to form the original graph
void addEdges(int a, int b)
{
    adj[a].push_back(b);
}

// add edges to form the inverse graph
void addEdgesInverse(int a, int b)
{
    adjInv[b].push_back(a);
}

// for STEP 1 of Kosaraju's Algorithm
void dfsFirst(int u)
{
    if (visited[u])
        return;

    visited[u] = 1;

    for (int i = 0; i < adj[u].size(); i++)
        dfsFirst(adj[u][i]);

    s.push(u);
}

// for STEP 2 of Kosaraju's Algorithm
void dfsSecond(int u)
{
    if (visitedInv[u])
        return;

    visitedInv[u] = 1;

    for (int i = 0; i < adjInv[u].size(); i++)
        dfsSecond(adjInv[u][i]);

    scc[u] = counter;
}

// function to check 2-Satisfiability
void is2Satisfiable(int n, int m, int a[], int b[])
{
    // adding edges to the graph
    for (int i = 0; i < m; i++)
    {
        // variable x is mapped to x
        // variable -x is mapped to n+x = n-(-x)

        // for a[i] or b[i], addEdges -a[i] -> b[i]
        // AND -b[i] -> a[i]
        if (a[i] > 0 && b[i] > 0)
        {
            addEdges(a[i] + n, b[i]);
            addEdgesInverse(a[i] + n, b[i]);
            addEdges(b[i] + n, a[i]);
            addEdgesInverse(b[i] + n, a[i]);
        }

        else if (a[i] > 0 && b[i] < 0)
        {
            addEdges(a[i] + n, n - b[i]);
            addEdgesInverse(a[i] + n, n - b[i]);
            addEdges(-b[i], a[i]);
            addEdgesInverse(-b[i], a[i]);
        }

        else if (a[i] < 0 && b[i] > 0)
        {
            addEdges(-a[i], b[i]);
            addEdgesInverse(-a[i], b[i]);
            addEdges(b[i] + n, n - a[i]);
            addEdgesInverse(b[i] + n, n - a[i]);
        }

        else
        {
            addEdges(-a[i], n - b[i]);
            addEdgesInverse(-a[i], n - b[i]);
            addEdges(-b[i], n - a[i]);
            addEdgesInverse(-b[i], n - a[i]);
        }
    }

    // STEP 1 of Kosaraju's Algorithm which
    // traverses the original graph
    for (int i = 1; i <= 2 * n; i++)
        if (!visited[i])
            dfsFirst(i);

    // STEP 2 of Kosaraju's Algorithm which
    // traverses the inverse graph. After this,
    // array scc[] stores the corresponding value
    while (!s.empty())
    {
        int n = s.top();
        s.pop();

        if (!visitedInv[n])
        {
            dfsSecond(n);
            counter++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        // for any 2 variable x and -x lie in
        // same SCC
        if (scc[i] == scc[i + n])
        {
            cout << "NAO" << endl;
            return;
        }
    }

    // no such variables x and -x exist which lie
    // in same SCC
    cout << "SIM"
         << endl;
    return;
}

// Driver function to test above functions
int main()
{
    // n is the number of variables
    // 2n is the total number of nodes
    // m is the number of clauses
    int n = 7499, m = 860;

    // each clause is of the form a or b
    // for m clauses, we have a[m], b[m]
    // representing a[i] or b[i]

    // Note:
    // 1 <= x <= N for an uncomplemented variable x
    // -N <= x <= -1 for a complemented variable x
    // -x is the complement of a variable x

    // The CNF being handled is:
    // '+' implies 'OR' and '*' implies 'AND'
    // (x1+x2)*(x2’+x3)*(x1’+x2’)*(x3+x4)*(x3’+x5)*
    // (x4’+x5’)*(x3’+x4)
    int a[] = {7318, -4071, 5545, -1658, 6510, -6547, 519, -2850, 3350, -3424, 7217, -4348, 2604, -3277, 5713, -2651, 610, -1695, 4506, -2287, 7227, -4929, 2181, -4311, 6957, -1664, 4267, -7490, 385, -6164, 5371, -3082, 4070, -2020, 1823, -3353, 7085, -737, 2653, -1347, 6639, -767, 6527, -3143, 5815, -2532, 4123, -2425, 2827, -5902, 6148, -2839, 1998, -6889, 2070, -6257, 1248, -6960, 4251, -925, 4906, -5710, 604, -6560, 6490, -5650, 4799, -1540, 5909, -2558, 3199, -311, 5096, -1351, 5631, -2628, 941, -5629, 7089, -6084, 407, -5139, 3298, -926, 4527, -4606, 3346, -1936, 6358, -6509, 2855, -5462, 2680, -1247, 6095, -6343, 366, -6652, 1977, -2601, 2036, -3075, 4886, -6081, 4169, -4841, 2026, -5535, 5196, -7036, 2261, -3604, 4810, -537, 7059, -624, 1098, -4326, 28, -1755, 6454, -2173, 4596, -880, 5541, -327, 2605, -7275, 4867, -3407, 7157, -3493, 3201, -1078, 1883, -1599, 4895, -2802, 3490, -1585, 1842, -192, 5447, -4752, 2206, -6610, 1236, -5350, 128, -2138, 6108, -3666, 4740, -4086, 2798, -2644, 924, -4460, 2771, -1640, 995, -5098, 1072, -6152, 4281, -5563, 5889, -5307, 5845, -2813, 2506, -5930, 2251, -3303, 7019, -2649, 7349, -5968, 6926, -3442, 1730, -47, 6339, -1482, 6940, -330, 2287, -4895, 4406, -5476, 1874, -5001, 5842, -4640, 884, -393, 0, -3933, 4051, -4794, 5794, -1562, 5702, -3070, 3143, -6541, 1415, -6267, 603, -1329, 805, -3938, 7485, -1695, 3823, -1547, 888, -7140, 5906, -3477, 613, -2141, 1798, -4131, 3488, -7124, 5029, -6467, 4733, -6233, 33, -4395, 30, -2318, 783, -7234, 7337, -4177, 4496, -1613, 2484, -6296, 4593, -2214, 4511, -3094, 6901, -3874, 5932, -1474, 4263, -1572, 1712, -4780, 3712, -5692, 2809, -86, 208, -2975, 2803, -3776, 5098, -6865, 7037, -6123, 6905, -1213, 5995, -4819, 2206, -6830, 5292, -3450, 804, -2227, 3070, -1506, 6055, -3485, 7165, -1558, 6532, -451, 5044, -4687, 3401, -7478, 4647, -289, 6087, -4255, 613, -2961, 1310, -6407, 3024, -3816, 3152, -5101, 677, -4684, 359, -3059, 1581, -7122, 134, -1147, 4382, -5823, 321, -5365, 1836, -6982, 5424, -4818, 6818, -1108, 6966, -2781, 140, -5385, 7137, -6934, 823, -5958, 5370, -788, 7011, -4733, 0, -6789, 4082, -6170, 2626, -7424, 6892, -5002, 3166, -3436, 191, -6717, 2345, -688, 1066, -2902, 7180, -3806, 6741, -1782, 6404, -4952, 6643, -3343, 1051, -233, 293, -1424, 2727, -3875, 3860, -4959, 3361, -6203, 6442, -143, 6628, -1037, 3987, -7433, 7011, -6982, 4596, -1697, 2039, -5293, 628, -2500, 3233, -6671, 6176, -6360, 2203, -3590, 6083, -3393, 3043, -769, 6490, -5568, 2067, -4461, 5425, -3987, 1500, -3840, 6906, -5293, 3871, -6596, 5247, -2889, 7213, -6465, 4799, -5410, 331, -1126, 4293, -4704, 1748, -6512, 6896, -2726, 3964, -5999, 1049, -5320, 3726, -2071, 2000, -143, 657, -4715, 5523, -6101, 775, -367, 7214, -2806, 4864, -6342, 1668, -6209, 1318, -1009, 6177, -1264, 3115, -1458, 5848, -7382, 4290, -6719, 285, -4845, 946, -2015, 5759, -6055, 6382, -375, 3429, -2909, 767, -2202, 116, -3052, 113, -2993, 5059, -1637, 65, -3886, 1152, -5218, 2319, -3373, 1106, -1935, 6445, -2323, 621, -4386, 3514, -2350, 552, -949, 4833, -4521, 3578, -5817, 5379, -5231, 6370, -5284, 763, -7457, 6547, -661, 3819, -6800, 5850, -5438, 4621, -7003, 4066, -4043, 312, -3105, 4975, -6446, 7417, -5341, 90, -6651, 4158, -992, 5775, -1726, 6557, -7088, 3573, -7157, 1711, -5212, 1167, -2362, 5726, -6277, 5592, -216, 4580, -3035, 1225, -3529, 2713, -4876, 6566, -3021, 2527, -114, 379, -5078, 5206, -144, 5851, -3545, 5555, -2476, 6789, -3064, 777, -4107, 4623, -4059, 2454, -7042, 6043, -4812, 4471, -5631, 2766, -4057, 6603, -5312, 7401, -4941, 4161, -2501, 1615, -2833, 6884, -4892, 5388, -2801, 7181, -265, 7349, -5798, 4481, -5962, 300, -5797, 3732, -6327, 6690, -2196, 1021, -67, 2396, -1775, 2676, -4194, 5847, -2598, 962, -2115, 2508, -360, 4147, -739, 2759, -7370, 5300, -6525, 2955, -866, 3479, -3177, 3602, -4911, 5534, -1186, 6259, -6635, 5771, -5568, 946, -6032, 1373, -2127, 1474, -476, 3037, -1553, 3820, -2425, 1649, -5539, 997, -4896, 6560, -4840, 4706, -6199, 5690, -4928, 3917, -6849, 4104, -642, 2241, -3545, 3458, -5718, 4993, -6572, 2038, -4158, 471, -5651, 5712, -3219, 3407, -2477, 6948, -4286, 5832, -6580, 5973, -3201, 6794, -3853, 3806, -7318, 1731, -7012, 677, -3041, 3850, -4202, 1046, -5940, 2676, -3224, 7462, -3888, 7164, -1172, 2595, -4081, 1582, -1697, 774, -3537, 174, -6330, 5811, -62, 2592, -3123, 2399, -3044, 2779, -991, 3317, -2008, 7220, -7428, 6152, -5016, 3208, -7150, 6740, -1196, 6334, -2182, 635, -2002, 2158, -1753, 3779, -2673, 3473, -4132, 5161, -1744, 6298, -2488, 5858, -101, 6910, -5369, 182, -6558, 4499, -3550, 2420, -1561, 5297, -3874, 1083, -3332, 4144, -1321, 7300, -5150, 1376, -5200, 3246, -3473, 3299, -769, 5517, -7226, 1343, -4691, 1483, -1424, 1344, -6477, 3832, -4169, 1042, -4236, 2051, -3352, 4157, -5514, 4388, -254, 2066, -5881, 2990, -6364, 3524, -2127, 6252, -4872, 2632, -6098, 3830, -796, 3364, -6668, 6705, -6049, 4387, -6763, 1759, -3112, 4044, -746, 2721, -6358, 1207, -6368, 4106, -5580, 1253, 0, 4099, -4356, 4440, -6970, 0, -3545, 4984, -3427, 2473, -5614, 1878, -1437, 3316, -3506, 1160, -7201, 3712, -128, 754, -2987, 486, -3639, 5561, -5169, 7450, -3924, 5995, -7358, 1781, -4605, 3009, -3055, 328, -2668, 3221, -1252, 6884, -3270, 878, -3883, 6677, -3057, 915, -281, 2212, -4583, 1742, -1387, 5653, -6639, 107, -4506, 388, -3325, 467, -1742, 7199, -648, 348, -4598, 5606, -2968, 4070, -995, 3510, -5828, 6600, -2992, 154, -1492, 318, -6867, 466, -707, 2923, -5395, 1062, -4309};
    int b[] = {558, -82, 2225, -1417, 6995, -865, 6323, -5265, 5782, -2079, 4422, -7288, 1503, -7073, 6657, -2651, 610, -6931, 4447, -3432, 3488, -4929, 1727, -4708, 4022, -1827, 2418, -3572, 38, -2194, 5885, -3082, 6718, -2974, 3616, -4071, 2091, -6961, 1883, -4021, 386, -1260, 7085, -3970, 1582, -2704, 4835, -2197, 665, -6797, 6148, -754, 599, -5337, 6678, -873, 1248, -3746, 6916, -3665, 35, -5854, 7001, -4063, 6578, -5944, 3168, -728, 1702, -122, 7124, -1130, 7372, -5675, 3413, -5873, 7415, -7281, 631, -1963, 6486, -5139, 836, -926, 4527, -6262, 3346, -1936, 5364, -6477, 5958, -5859, 6744, -60, 6956, -4016, 366, -2659, 6093, -7466, 6717, -893, 2030, -6172, 2757, -3352, 2994, -2965, 772, -7036, 1109, -7087, 4810, -4359, 788, -6448, 2135, -3886, 2414, -1755, 1189, -1888, 709, -880, 5541, -327, 3492, -3434, 6796, -3685, 6987, -7354, 4941, -4655, 7282, -3003, 340, -2802, 155, -5916, 7424, -192, 801, -4752, 6483, -1336, 1214, -4074, 1274, -6707, 1962, -5268, 4740, -4086, 4856, -932, 6866, -1108, 2503, -1640, 995, -5242, 3700, -3326, 4281, -5563, 5889, -651, 3413, -2813, 2410, -5930, 2654, -4938, 7019, -1454, 6402, -6420, 1008, -6837, 2531, -1885, 1082, -7312, 4338, -7455, 2208, -4895, 4314, -147, 1874, -4419, 5149, -3589, 4459, -393, 0, -1694, 4051, -6748, 2331, -5672, 5702, -5531, 3143, -2464, 2638, -6267, 3049, -1329, 7347, -4274, 3586, -1695, 3823, -6958, 1834, -3348, 3588, -5679, 7417, -2141, 1798, -4131, 3488, -4866, 5029, -6218, 4733, -6757, 4024, -2480, 2429, -2034, 5623, -1559, 63, -1069, 5436, -3603, 2484, -6265, 6858, -4503, 2757, -5452, 7155, -554, 3269, -2528, 1239, -1572, 1712, -6910, 3712, -5692, 2739, -634, 208, -5736, 1197, -883, 4537, -3667, 6012, -6123, 3346, -4970, 5995, -3385, 2709, -6830, 2279, -3450, 5334, -7255, 3323, -2958, 4592, -3485, 1955, -807, 6078, -6062, 5044, -4789, 3935, -6790, 6637, -1983, 6087, -4055, 1442, -2961, 4505, -7341, 3024, -3816, 6871, -641, 924, -4684, 3540, -2808, 1024, -1452, 5982, -5709, 1885, -5823, 6306, -5022, 4818, -408, 5613, -2687, 2847, -7271, 7180, -2005, 5970, -3904, 134, -4012, 3032, -6599, 6369, -788, 1102, -6046, 0, -6606, 3404, -3373, 4290, -7424, 275, -5785, 3166, -2261, 581, -5851, 6400, -688, 6195, -7145, 6339, -1114, 6741, -6246, 952, -2468, 6643, -438, 5088, -233, 1873, -3572, 5268, -3875, 6068, -398, 6334, -6203, 5186, -2371, 6884, -3168, 3987, -4662, 3344, -2198, 728, -1697, 4112, -5293, 5060, -300, 3369, -802, 6176, -6838, 4743, -1887, 5313, -575, 5017, -803, 4839, -1577, 4480, -6154, 6254, -3987, 1500, -259, 5863, -5293, 6699, -1772, 6064, -2889, 2020, -7485, 5981, -5410, 2302, -7489, 4293, -5021, 1748, -6148, 4687, -7341, 6322, -650, 1258, -2993, 7430, -2453, 2000, -5206, 3190, -2665, 7414, -6755, 775, -3846, 6069, -7299, 4864, -1884, 6687, -6883, 7258, -6102, 6177, -3159, 887, -1670, 4228, -6599, 6233, -6719, 2353, -3722, 6140, -6149, 3891, -1555, 1928, -6012, 3429, -1013, 1783, -5945, 6000, -763, 2085, -6754, 7050, -4677, 1805, -3383, 618, -4254, 692, -6965, 1106, -1522, 3353, -5028, 621, -1359, 3460, -4894, 6964, -3691, 2662, -4521, 836, -5817, 6531, -3036, 6370, -2274, 7030, -1333, 5464, -5314, 404, -4459, 4667, -6081, 1130, -2072, 2454, -4043, 1618, -5827, 4458, -1702, 675, -977, 803, -6651, 4158, -992, 7041, -2219, 244, -90, 4678, -3914, 4532, -1523, 1213, -6039, 5272, -2150, 5592, -4741, 5199, -3035, 4483, -3738, 3327, -2738, 5359, -4917, 6476, -494, 5232, -5078, 5206, -144, 824, -1902, 6273, -2476, 4483, -3712, 7100, -3070, 70, -1114, 4314, -2286, 573, -490, 1382, -4929, 2766, -3933, 3426, -5722, 7401, -4941, 3961, -2501, 4980, -458, 3684, -603, 2932, -6658, 5519, -265, 6387, -6907, 7196, -7473, 1900, -5797, 1117, -6327, 583, -3210, 5501, -4769, 1533, -4696, 3379, -7134, 4650, -4236, 1449, -6306, 1964, -3680, 5303, -4869, 1395, -7370, 5300, -4586, 5471, -671, 3479, -3177, 6935, -5406, 6510, -1186, 963, -1641, 2021, -5568, 5485, -4386, 2054, -5301, 146, -3703, 3580, -1553, 3820, -2425, 5974, -684, 632, -6486, 6898, -5976, 6166, -6199, 6454, -4928, 1272, -3256, 1483, -5096, 2907, -1918, 761, -5718, 3375, -1708, 2038, -161, 2244, -5898, 5629, -5290, 6240, -2477, 2976, -4286, 1787, -1187, 1955, -3201, 786, -5965, 162, -1521, 2885, -7012, 3490, -3041, 6663, -6813, 5410, -276, 2676, -6410, 4356, -4619, 1325, -48, 1616, -6531, 519, -1697, 3934, -4874, 4151, -7301, 3261, -4270, 4257, -1900, 2399, -1341, 4650, -1220, 3317, -1972, 4117, -502, 6152, -5016, 3208, -4493, 1881, -1196, 5113, -618, 3117, -2002, 2158, -7119, 3549, -1704, 6055, -4132, 6888, -140, 2011, -4607, 5858, -6095, 4284, -1319, 2161, -5888, 5618, -1492, 1524, -1561, 45, -1300, 5634, -6211, 2706, -3477, 7300, -3022, 1376, -5750, 627, -2662, 1645, -7265, 3207, -4178, 5565, -4691, 3876, -1676, 1344, -6477, 1419, -662, 4867, -5027, 1285, -5887, 6444, -2080, 3295, -254, 1906, -5881, 358, -4287, 2624, -2127, 2007, -2613, 2632, -735, 3837, -796, 1448, -7310, 6705, -4357, 4630, -4112, 5145, -3112, 4044, -5153, 2719, -6943, 453, -7286, 5277, -5399, 6611, 0, 5765, -3005, 7441, -6936, 0, -7220, 2843, -941, 6630, -5173, 2360, -1437, 7349, -909, 1928, -4046, 167, -707, 5522, -1974, 3662, -5289, 3253, -2898, 5441, -5066, 6433, -5762, 1781, -1198, 2912, -3887, 4099, -1782, 6679, -3236, 1595, -5097, 2246, -3348, 350, -3057, 915, -281, 5075, -4583, 1742, -3907, 5261, -3735, 7385, -4798, 6315, -3325, 3172, -3336, 5323, -7160, 646, -1511, 5606, -5832, 919, -1022, 1727, -4062, 1188, -4558, 2062, -5078, 680, -5686, 114, -6227, 2923, -1401, 5190, -4524};

    // We have considered the same example for which
    // Implication Graph was made
    is2Satisfiable(n, m, a, b);

    return 0;
}
