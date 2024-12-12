#include "DefaultPersonalizationData.h"

const char *defaultRoundsMatches = // Berger's Table
R"(
{
    "r1": [
        { "t1": 1, "t2": 8 },
        { "t1": 2, "t2": 7 },
        { "t1": 3, "t2": 6 },
        { "t1": 4, "t2": 5 }
    ],
    "r2": [
        { "t1": 8, "t2": 5 },
        { "t1": 6, "t2": 4 },
        { "t1": 7, "t2": 3 },
        { "t1": 1, "t2": 2 }
    ],
    "r3": [
        { "t1": 2, "t2": 8 },
        { "t1": 3, "t2": 1 },
        { "t1": 4, "t2": 7 },
        { "t1": 5, "t2": 6 }
    ],
    "r4": [
        { "t1": 8, "t2": 6 },
        { "t1": 7, "t2": 5 },
        { "t1": 1, "t2": 4 },
        { "t1": 2, "t2": 3 }
    ],
    "r5": [
        { "t1": 3, "t2": 8 },
        { "t1": 4, "t2": 2 },
        { "t1": 5, "t2": 1 },
        { "t1": 6, "t2": 7 }
    ],
    "r6": [
        { "t1": 8, "t2": 7 },
        { "t1": 1, "t2": 6 },
        { "t1": 2, "t2": 5 },
        { "t1": 3, "t2": 4 }
    ],
    "r7": [
        { "t1": 4, "t2": 8 },
        { "t1": 5, "t2": 3 },
        { "t1": 6, "t2": 2 },
        { "t1": 7, "t2": 1 }
    ]
}
)";

const char *defaultExampleData =
R"(
{
    "teams": [
        {
            "team name": "Boule Masters",
            "players": [
                {
                    "fname": "Michael",
                    "lname": "Brown",
                    "license": "L1828",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": true
                },
                {
                    "fname": "James",
                    "lname": "Williams",
                    "license": "L3119",
                    "age group": 0,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "John",
                    "lname": "Anderson",
                    "license": "L4000",
                    "age group": 3,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Wilson",
                    "license": "L3017",
                    "age group": 0,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Daniel",
                    "lname": "Davis",
                    "license": "L2472",
                    "age group": 3,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "John",
                    "lname": "Brown",
                    "license": "L8923",
                    "age group": 2,
                    "gender": 0,
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Srebrne Kule",
            "players": [
                {
                    "fname": "Isabella",
                    "lname": "Williams",
                    "license": "L7277",
                    "age group": 2,
                    "gender": 0,
                    "isTeamLeader": true
                },
                {
                    "fname": "Emma",
                    "lname": "Thomas",
                    "license": "L1581",
                    "age group": 0,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Johnson",
                    "license": "L1022",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Thomas",
                    "license": "L3601",
                    "age group": 1,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Williams",
                    "license": "L1060",
                    "age group": 2,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Thomas",
                    "license": "L2403",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Petanque Pasja",
            "players": [
                {
                    "fname": "Emma",
                    "lname": "Williams",
                    "license": "L3286",
                    "age group": 3,
                    "gender": 1,
                    "isTeamLeader": true
                },
                {
                    "fname": "David",
                    "lname": "Davis",
                    "license": "L7003",
                    "age group": 0,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "Olivia",
                    "lname": "Johnson",
                    "license": "L7275",
                    "age group": 3,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Miller",
                    "license": "L2834",
                    "age group": 2,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "David",
                    "lname": "Brown",
                    "license": "L9907",
                    "age group": 0,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Anderson",
                    "license": "L4332",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Stalowe Rzuty",
            "players": [
                {
                    "fname": "John",
                    "lname": "Moore",
                    "license": "L9791",
                    "age group": 2,
                    "gender": 1,
                    "isTeamLeader": true
                },
                {
                    "fname": "John",
                    "lname": "Williams",
                    "license": "L3168",
                    "age group": 0,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Davis",
                    "license": "L3581",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "John",
                    "lname": "Miller",
                    "license": "L6838",
                    "age group": 2,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Moore",
                    "license": "L4738",
                    "age group": 1,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Olivia",
                    "lname": "Miller",
                    "license": "L7759",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Mistrzowie Klasyki",
            "players": [
                {
                    "fname": "Emily",
                    "lname": "Davis",
                    "license": "L9489",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": true
                },
                {
                    "fname": "James",
                    "lname": "Miller",
                    "license": "L6546",
                    "age group": 2,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Ava",
                    "lname": "Taylor",
                    "license": "L9274",
                    "age group": 0,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Smith",
                    "license": "L8696",
                    "age group": 3,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "Daniel",
                    "lname": "Smith",
                    "license": "L4830",
                    "age group": 2,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Thomas",
                    "license": "L5877",
                    "age group": 1,
                    "gender": 1,
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Kule i Stal",
            "players": [
                {
                    "fname": "David",
                    "lname": "Anderson",
                    "license": "L5177",
                    "age group": 2,
                    "gender": 0,
                    "isTeamLeader": true
                },
                {
                    "fname": "Olivia",
                    "lname": "Miller",
                    "license": "L9196",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Brown",
                    "license": "L2400",
                    "age group": 0,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Johnson",
                    "license": "L2216",
                    "age group": 3,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Williams",
                    "license": "L8053",
                    "age group": 1,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Moore",
                    "license": "L4951",
                    "age group": 2,
                    "gender": 1,
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Słońce Prowansji",
            "players": [
                {
                    "fname": "Daniel",
                    "lname": "Moore",
                    "license": "L3530",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": true
                },
                {
                    "fname": "Daniel",
                    "lname": "Moore",
                    "license": "L7605",
                    "age group": 1,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Brown",
                    "license": "L8251",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Brown",
                    "license": "L5737",
                    "age group": 0,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Smith",
                    "license": "L5452",
                    "age group": 3,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Miller",
                    "license": "L6121",
                    "age group": 0,
                    "gender": 1,
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Bouliści",
            "players": [
                {
                    "fname": "Ava",
                    "lname": "Miller",
                    "license": "L5907",
                    "age group": 3,
                    "gender": 1,
                    "isTeamLeader": true
                },
                {
                    "fname": "Ava",
                    "lname": "Miller",
                    "license": "L7026",
                    "age group": 0,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "Michael",
                    "lname": "Williams",
                    "license": "L7350",
                    "age group": 2,
                    "gender": 1,
                    "isTeamLeader": false
                },
                {
                    "fname": "Ava",
                    "lname": "Smith",
                    "license": "L8990",
                    "age group": 2,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "David",
                    "lname": "Johnson",
                    "license": "L1413",
                    "age group": 0,
                    "gender": 0,
                    "isTeamLeader": false
                },
                {
                    "fname": "Olivia",
                    "lname": "Thomas",
                    "license": "L4110",
                    "age group": 2,
                    "gender": 1,
                    "isTeamLeader": false
                }
            ]
        }
    ]
}
)";
