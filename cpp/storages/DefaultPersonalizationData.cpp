#include "DefaultPersonalizationData.h"

const char *defaultServerAddress = "http://127.0.0.1:5000/api";
// const char *defaultServerAddress = "http://192.168.0.70:5000/api";
// const char *defaultServerAddress = "http://192.168.0.72:5000/api";

const char *defaultRoundsMatches = // Berger's Table
R"(
{
    "phase 1": [
        [
            { "t1": 1, "t2": 8 },
            { "t1": 2, "t2": 7 },
            { "t1": 3, "t2": 6 },
            { "t1": 4, "t2": 5 }
        ],
        [
            { "t1": 8, "t2": 5 },
            { "t1": 6, "t2": 4 },
            { "t1": 7, "t2": 3 },
            { "t1": 1, "t2": 2 }
        ],
        [
            { "t1": 2, "t2": 8 },
            { "t1": 3, "t2": 1 },
            { "t1": 4, "t2": 7 },
            { "t1": 5, "t2": 6 }
        ],
        [
            { "t1": 8, "t2": 6 },
            { "t1": 7, "t2": 5 },
            { "t1": 1, "t2": 4 },
            { "t1": 2, "t2": 3 }
        ],
        [
            { "t1": 3, "t2": 8 },
            { "t1": 4, "t2": 2 },
            { "t1": 5, "t2": 1 },
            { "t1": 6, "t2": 7 }
        ],
        [
            { "t1": 8, "t2": 7 },
            { "t1": 1, "t2": 6 },
            { "t1": 2, "t2": 5 },
            { "t1": 3, "t2": 4 }
        ],
        [
            { "t1": 4, "t2": 8 },
            { "t1": 5, "t2": 3 },
            { "t1": 6, "t2": 2 },
            { "t1": 7, "t2": 1 }
        ]
    ],
    "phase 2": [
        [
            { "t1": 1, "t2": 4 },
            { "t1": 2, "t2": 3 }
        ],
        [
            { "t1": 1, "t2": 3 },
            { "t1": 2, "t2": 4 }
        ],
        [
            { "t1": 1, "t2": 2 },
            { "t1": 3, "t2": 4 }
        ]
    ]
}
)";

const char *defaultExampleData =
R"(
{
    "event details": {
        "event name": "Mistrzostwa Polski",
        "event first phase date": "2025-06-18",
        "event second phase date": "2025-08-23",
        "event competition organizer": "Jan Kowalski",
        "event second phase place": "Warszawa",
        "event first phase place": "Kraków",
        "event union delegate": "Tomasz Karolak",
        "event judges": [
            "Sędzia 1",
            "Sędzia zapasowy",
            "Marcin Dodatek"
        ]
    },
    "teams": [
        {
            "name": "Boule Masters",
            "players": [
                {
                    "first name": "Michael",
                    "last name": "Brown",
                    "license": "L1828",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": true
                },
                {
                    "first name": "James",
                    "last name": "Williams",
                    "license": "L3119",
                    "age group": "junior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "John",
                    "last name": "Anderson",
                    "license": "L4000",
                    "age group": "veteran",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "Emma",
                    "last name": "Wilson",
                    "license": "L3017",
                    "age group": "junior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Daniel",
                    "last name": "Davis",
                    "license": "L2472",
                    "age group": "veteran",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "John",
                    "last name": "Brown",
                    "license": "L8923",
                    "age group": "senior",
                    "gender": "male",
                    "is team leader": false
                }
            ]
        },
        {
            "name": "Srebrne Kule",
            "players": [
                {
                    "first name": "Isabella",
                    "last name": "Williams",
                    "license": "L7277",
                    "age group": "senior",
                    "gender": "male",
                    "is team leader": true
                },
                {
                    "first name": "Emma",
                    "last name": "Thomas",
                    "license": "L1581",
                    "age group": "junior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Sophia",
                    "last name": "Johnson",
                    "license": "L1022",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "James",
                    "last name": "Thomas",
                    "license": "L3601",
                    "age group": "youth",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "James",
                    "last name": "Williams",
                    "license": "L1060",
                    "age group": "senior",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "Sophia",
                    "last name": "Thomas",
                    "license": "L2403",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": false
                }
            ]
        },
        {
            "name": "Petanque Pasja",
            "players": [
                {
                    "first name": "Emma",
                    "last name": "Williams",
                    "license": "L3286",
                    "age group": "veteran",
                    "gender": "female",
                    "is team leader": true
                },
                {
                    "first name": "David",
                    "last name": "Davis",
                    "license": "L7003",
                    "age group": "junior",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "Olivia",
                    "last name": "Johnson",
                    "license": "L7275",
                    "age group": "veteran",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "James",
                    "last name": "Miller",
                    "license": "L2834",
                    "age group": "senior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "David",
                    "last name": "Brown",
                    "license": "L9907",
                    "age group": "junior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Chris",
                    "last name": "Anderson",
                    "license": "L4332",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": false
                }
            ]
        },
        {
            "name": "Stalowe Rzuty",
            "players": [
                {
                    "first name": "John",
                    "last name": "Moore",
                    "license": "L9791",
                    "age group": "senior",
                    "gender": "female",
                    "is team leader": true
                },
                {
                    "first name": "John",
                    "last name": "Williams",
                    "license": "L3168",
                    "age group": "junior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Chris",
                    "last name": "Davis",
                    "license": "L3581",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "John",
                    "last name": "Miller",
                    "license": "L6838",
                    "age group": "senior",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "Sophia",
                    "last name": "Moore",
                    "license": "L4738",
                    "age group": "youth",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Olivia",
                    "last name": "Miller",
                    "license": "L7759",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": false
                }
            ]
        },
        {
            "name": "Mistrzowie Klasyki",
            "players": [
                {
                    "first name": "Emily",
                    "last name": "Davis",
                    "license": "L9489",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": true
                },
                {
                    "first name": "James",
                    "last name": "Miller",
                    "license": "L6546",
                    "age group": "senior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Ava",
                    "last name": "Taylor",
                    "license": "L9274",
                    "age group": "junior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Sophia",
                    "last name": "Smith",
                    "license": "L8696",
                    "age group": "veteran",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "Daniel",
                    "last name": "Smith",
                    "license": "L4830",
                    "age group": "senior",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "James",
                    "last name": "Thomas",
                    "license": "L5877",
                    "age group": "youth",
                    "gender": "female",
                    "is team leader": false
                }
            ]
        },
        {
            "name": "Kule i Stal",
            "players": [
                {
                    "first name": "David",
                    "last name": "Anderson",
                    "license": "L5177",
                    "age group": "senior",
                    "gender": "male",
                    "is team leader": true
                },
                {
                    "first name": "Olivia",
                    "last name": "Miller",
                    "license": "L9196",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Emma",
                    "last name": "Brown",
                    "license": "L2400",
                    "age group": "junior",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "Chris",
                    "last name": "Johnson",
                    "license": "L2216",
                    "age group": "veteran",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "James",
                    "last name": "Williams",
                    "license": "L8053",
                    "age group": "youth",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Emma",
                    "last name": "Moore",
                    "license": "L4951",
                    "age group": "senior",
                    "gender": "female",
                    "is team leader": false
                }
            ]
        },
        {
            "name": "Słońce Prowansji",
            "players": [
                {
                    "first name": "Daniel",
                    "last name": "Moore",
                    "license": "L3530",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": true
                },
                {
                    "first name": "Daniel",
                    "last name": "Moore",
                    "license": "L7605",
                    "age group": "youth",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "James",
                    "last name": "Brown",
                    "license": "L8251",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "James",
                    "last name": "Brown",
                    "license": "L5737",
                    "age group": "junior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Emma",
                    "last name": "Smith",
                    "license": "L5452",
                    "age group": "veteran",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Chris",
                    "last name": "Miller",
                    "license": "L6121",
                    "age group": "junior",
                    "gender": "female",
                    "is team leader": false
                }
            ]
        },
        {
            "name": "Bouliści",
            "players": [
                {
                    "first name": "Ava",
                    "last name": "Miller",
                    "license": "L5907",
                    "age group": "veteran",
                    "gender": "female",
                    "is team leader": true
                },
                {
                    "first name": "Ava",
                    "last name": "Miller",
                    "license": "L7026",
                    "age group": "junior",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "Michael",
                    "last name": "Williams",
                    "license": "L7350",
                    "age group": "senior",
                    "gender": "female",
                    "is team leader": false
                },
                {
                    "first name": "Ava",
                    "last name": "Smith",
                    "license": "L8990",
                    "age group": "senior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "David",
                    "last name": "Johnson",
                    "license": "L1413",
                    "age group": "junior",
                    "gender": "male",
                    "is team leader": false
                },
                {
                    "first name": "Olivia",
                    "last name": "Thomas",
                    "license": "L4110",
                    "age group": "senior",
                    "gender": "female",
                    "is team leader": false
                }
            ]
        }
    ]
}
)";
