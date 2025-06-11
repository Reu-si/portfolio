import 'package:bee_bloom/constants/sizes.dart';
import 'package:bee_bloom/data/pflanze.dart';
import 'package:bee_bloom/data/pflanzendaten.dart';
import 'package:bee_bloom/pages/survey_page.dart';
import 'package:bee_bloom/widgets/plantcard.dart';
import 'package:flutter/material.dart';
import '../constants/constants.dart';
import '../services/storage_service.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'dart:convert';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  List<Pflanze> pflanzenShuffled = List.from(pflanzen);
  late List<Pflanze> fivePflanzen = pflanzenShuffled;
  late List<Pflanze> deinePflanzen = [];
  int waterStreak = 0;
  int userLevel = 0;

  List<Map<int, bool>> answers = [
    {
      0 : false,
      1 : false,
      2 : false,
      3 : false
    }
  ];

  @override
  void initState() {
    pflanzenShuffled.shuffle();
    super.initState();
    loadInitialData();
  }

  Future<void> loadInitialData() async {
    await loadAnswers();
    loadPflanzen();
    await loadWaterStreak();
    await loadUserLevel();
  }


  Future<void> loadAnswers() async {
    SharedPreferences prefs = await SharedPreferences.getInstance();

    // Lade und dekodiere die Antworten
    List<String>? answerList = prefs.getStringList('answers');
    if (answerList != null) {
      setState(() {
        answers = answerList.map((jsonString) {
          Map<String, dynamic> map = jsonDecode(jsonString);
          return map.map((key, value) =>
              MapEntry(int.parse(key), value as bool));
        }).toList();
        //print(answers);
      });
    } else {
      setState(() {
        answers = [];
      });
    }
  }

  void loadPflanzen(){
    List<Pflanze> auswahl = [];

    //Pflanzenvorschläge filtern
    for (var pflanze in pflanzenShuffled) {
      bool ausgewaehlt = true;

      //Erfahrung <-> Pflege
      //print(pflanze);
      //print(pflanze.pflege);
      if (answers[0][2]! || answers[0][3]!){ // geringe Erfahrung
        if (pflanze.pflege == "mittlere Pflege") {
          ausgewaehlt = false;
          continue;
        }
      }
      //Location <-> Sonne
      //print(pflanze.sonne);
      if (answers[1][1]! || answers[1][2]!){ // Volle Sonne (Balkon oder Garten)
        if (pflanze.sonne != "volle Sonne") {
          ausgewaehlt = false;
          continue;
        }
      }
      //Abwesenheit <-> wateringCycle
      //print(pflanze.wateringCycle);
      if (answers[2][0]!){ // Oft weg
        if (pflanze.wateringCycle < 3) {
          ausgewaehlt = false;
          continue;
        }
      }
      //Haustiere/Allergien <-> giftig
      //print(pflanze.giftig);
      if (answers[3][0]! || answers[4][1]!){ // Haustier oder Allergie vorhanden
        if (pflanze.giftig != "nicht giftig") {
          ausgewaehlt = false;
          continue;
        }
      }
      //Luftfeuchtigkeit <-> trocken
      //print(pflanze.trocken);
      if (answers[4][3]!){ // Trocken
        if (pflanze.trocken == "frisch bis trocken") {
          ausgewaehlt = false;
          continue;
        }
      }
      if (ausgewaehlt){
        auswahl.add(pflanze);
      }
      if (auswahl.length >= 5) {
        break;
      }
    }

    //print(auswahl);
    deinePflanzen = auswahl;
  }

  List<Widget> erzeugePlantCards() {
    List<Widget> widgets = [];

    for (var pflanze in deinePflanzen) {
      if (deinePflanzen.indexOf(pflanze) != deinePflanzen.length - 1){
        widgets.add(Plantcard(title: pflanze.name, imageUrl: pflanze.bildpfad));
      }else{
        widgets.add(
            Padding(
              padding: EdgeInsets.only(bottom: Sizes.paddingRegular),
              child: Plantcard(
                  title: pflanze.name,
                  imageUrl: pflanze.bildpfad),
            )
        );
      }

    }

    return widgets;
  }

  @override
  Widget build(BuildContext context) {
    return Stack(
      //mainAxisSize: MainAxisSize.min,
      children: [
        SingleChildScrollView(
          child: Column(
            children: [
              SizedBox(
                height: Sizes.bottomNavigationHeight,
              ),
              Container(
                padding: EdgeInsets.all(Sizes.paddingSmall),
                margin: EdgeInsets.only(
                    top: 20,
                    left: 20,
                    right: 20
                ),
                width: double.infinity,
                height: 200,
                decoration: BoxDecoration(
                  color: lightgrey,
                  borderRadius: BorderRadius.circular(15),
                ),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      "Meine Erfolge",
                        style: TextStyle(
                          //fontFamily: "Roboto",
                          fontWeight: FontWeight.bold,
                          fontSize: 15,
                        )
                    ),
                    Container(
                      padding: EdgeInsets.only(
                        top: Sizes.paddingRegular,
                      ),
                      child: Row(
                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                        children: [
                          Container(
                            width: 80,
                            child: Image(
                              image: AssetImage(getWaterCanImagePath(waterStreak)),
                              //fit: BoxFit.fill,
                            ),
                          ),
                          Container(
                            width: 80,
                            child: Image(
                              image: AssetImage(getBeeImagePath(userLevel)),
                              //fit: BoxFit.fill,
                            ),
                          ),
                        ],
                      )
                    ),
                    Container(
                        padding: EdgeInsets.only(
                          top: Sizes.paddingSmall,
                        ),
                        child: Row(
                          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                          children: [
                            Container(
                              width: 70,
                              child: RichText(
                                  textAlign: TextAlign.center,
                                  text: TextSpan(
                                      children: <TextSpan> [
                                        TextSpan(
                                            text: '$waterStreak',
                                            style: TextStyle(
                                                fontWeight: FontWeight.bold,
                                                fontSize: 15,
                                                color: Color.fromARGB(255, 13, 182, 219)
                                            )),
                                        TextSpan(
                                            text: ' Tage',
                                            style: TextStyle(
                                              fontWeight: FontWeight.bold,
                                              fontSize: 15,
                                              color: black,
                                            )
                                        )
                                      ]
                                  )
                              ),
                            ),
                            Container(
                              width: 70,
                              child: RichText(
                                textAlign: TextAlign.center,
                                  text: TextSpan(
                                      children: <TextSpan> [
                                        TextSpan(
                                            text: 'Level',
                                            style: TextStyle(
                                                fontWeight: FontWeight.bold,
                                                fontSize: 15,
                                                color: black
                                            )),
                                        TextSpan(
                                            text: ' $userLevel',
                                            style: TextStyle(
                                              fontWeight: FontWeight.bold,
                                              fontSize: 15,
                                              color: green,
                                            )
                                        )
                                      ]
                                  )
                              ),
                            ),
                          ],
                        )
                    )
                  ],
                ),
              ),
          Container(
            margin: EdgeInsets.only(
                top: 20,
                left: 20,
                right: 20
            ),
            alignment: Alignment.centerLeft,
            child: Text(
              "Pflanzen für Dich",
              style: TextStyle(
                fontWeight: FontWeight.bold,
                fontSize: 20,
              ),
            ),
          ),
              Column(
                children: erzeugePlantCards(),
              ),
            ],
          ),
        ),
        Container(
            padding: EdgeInsets.only(
              left: 15,
              right: 15,
              top: 5,
              bottom: 5,
            ),
            decoration: const BoxDecoration(
                color: white,
                boxShadow: [
                  BoxShadow(
                    color: darkgrey,
                    spreadRadius: 5,
                    blurRadius: 7,
                    offset: Offset(0, 2), // changes position of shadow
                  ),]
            ),
            width: double.infinity,
            height: Sizes.bottomNavigationHeight,
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,                  //crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Container(
                  width: 40,
                  child: ClipRRect(
                    borderRadius: BorderRadius.circular(100),
                    child: Image(
                      image: AssetImage('images/logo.png'),
                      fit: BoxFit.fill,
                    ),
                  ),
                ),
                Text(
                  "BeeBloom",
                  style: TextStyle(
                    fontWeight: FontWeight.bold,
                    fontSize: 25,
                  ),
                ),
                Container(
                  width: 40,
                  padding: EdgeInsets.all(6),
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(50),
                    border: Border.all(
                      color: black,
                      width: 2,
                    ),
                  ),
                  child: GestureDetector(
                    onTap: () {
                      Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (context) => SurveyPage()));
                    },
                    child: Icon(
                      Icons.content_paste_search_rounded,
                      color: black,
                      //size: 15,
                    ),
                  ),
                ),
              ],
            )
        ),
      ],
    );
  }

  Future<void> loadWaterStreak() async {
    int streak = await StorageService.getWaterStreak();
    setState(() {
      waterStreak = streak;
    });
  }

  Future<void> loadUserLevel() async {
    int level = await StorageService.getUserLevel();
    setState(() {
      userLevel = level;
    });
  }

  String getBeeImagePath(int userLevel) {
    if (userLevel >= 5) {
      return 'images/biene_level5.png';
    } else if (userLevel >= 4) {
      return 'images/biene_level4.png';
    } else if (userLevel >= 3) {
      return 'images/biene_level3.png';
    } else if (userLevel >= 2) {
      return 'images/biene_level2.png';
    } else {
      return 'images/biene_level1.png';
    }
  }

  String getWaterCanImagePath(int waterStreak) {
    if (waterStreak >= 10) {
      return 'images/watercan_veryhappy.png';
    } else if (waterStreak >= 5) {
      return 'images/watercan_happy.png';
    } else if (waterStreak > 2) {
      return 'images/watercan_neutral.png';
    } else {
      return 'images/watercan_sad.png';
    }
  }
}
