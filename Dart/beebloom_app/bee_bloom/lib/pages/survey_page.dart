import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/constants/sizes.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:boxicons/boxicons.dart';
import 'main_page.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'dart:convert';


class SurveyPage extends StatefulWidget {
  const SurveyPage({super.key});

  @override
  State<SurveyPage> createState() => _SurveyPageState();
}

class _SurveyPageState extends State<SurveyPage> {
  List<Map<String, dynamic>> questions = [
    {
      "question" : "Wie viel Erfahrung hast du im Thema Botanik?", //pflege
      "answers" :   [
        "Sehr erfahren",
        "Mittel erfahren",
        "Wenig erfahren",
        "Neuling"
      ]
    },
    {
      "question" : "An welchem Ort möchtest du deine Pflanzen halten?", //sonne
      "answers" :   [
        "In der Wohnung",
        "Auf dem Balkon",
        "Im Garten",
        "Im Keller"
      ]
    },
    {
      "question" : "Lässt du deine Pflanzen öfters alleine?", //wateringCycle
      "answers" :   [
        "Mehrmals die Woche",
        "Manchmal",
        "Nur Selten",
        "Niemals"
      ]
    },
    {
      "question" : "Besitzt du Haustiere oder hast Allergien?", //giftig
      "answers" :   [
        "Ich habe Haustiere",
        "Ich habe Allergien",
        "Ich habe keine Haustiere",
        "Weder noch"
      ]
    },
    {
      "question" : "Wie ist die Luftfeuchtigkeit an deinem Ort?", //trocken
      "answers" :   [
        "Sehr Feucht",
        "Feucht",
        "Mittel",
        "Trocken"
      ]
    },
  ];

  int questionCount = 0;

  List<Map<int, bool>> answers= [
    {
      0 : false,
      1 : false,
      2 : false,
      3 : false
    }
  ];

  List<List<Color>> answerBoxColor = [
    [white, white, white, white]
  ];
  List<List<Color>> answerTextColor = [
    [green, green, green, green]
  ];

  bool _isPressed = false;

  @override
  void initState() {
    super.initState();
    loadProfileData();
  }

  // Funktion zum Speichern der Daten
  Future<void> saveProfileData(List<Map<int, bool>> answers, List<List<Color>> answerBoxColor, List<List<Color>> answerTextColor) async {
    SharedPreferences prefs = await SharedPreferences.getInstance();

    // Konvertiere die Antworten in eine JSON-kompatible Liste (Key als String speichern)
    List<String> answerList = answers.map((map) {
      return jsonEncode(map.map((key, value) => MapEntry(key.toString(), value)));
    }).toList();
    prefs.setStringList('answers', answerList);

    // Konvertiere die Farben in ein JSON-kompatibles Format
    List<String> boxColors = answerBoxColor.map((list) => jsonEncode(list.map((color) => color.value).toList())).toList();
    prefs.setStringList('answerBoxColor', boxColors);

    List<String> textColors = answerTextColor.map((list) => jsonEncode(list.map((color) => color.value).toList())).toList();
    prefs.setStringList('answerTextColor', textColors);
  }

  Future<void> loadProfileData() async {
    SharedPreferences prefs = await SharedPreferences.getInstance();

    // Lade und dekodiere die Antworten
    List<String>? answerList = prefs.getStringList('answers');
    //print(answerList);
    if (answerList != null) {
      setState(() {
        answers = answerList.map((jsonString) {
          Map<String, dynamic> map = jsonDecode(jsonString);
          return map.map((key, value) => MapEntry(int.parse(key), value as bool));
        }).toList();
        //print(answers);
      });
    } else {
      setState(() {
        answers = [];
      });
    }

    // Lade und dekodiere die Box-Farben
    List<String>? boxColorList = prefs.getStringList('answerBoxColor');
    if (boxColorList != null) {
      setState(() {
        answerBoxColor = boxColorList.map((jsonString) {
          List<dynamic> list = jsonDecode(jsonString);
          return list.map((colorValue) => Color(colorValue as int)).toList();
        }).toList();
      });
    } else {
      setState(() {
        answerBoxColor = [];
      });
    }

    // Lade und dekodiere die Text-Farben
    List<String>? textColorList = prefs.getStringList('answerTextColor');
    if (textColorList != null) {
      setState(() {
        answerTextColor = textColorList.map((jsonString) {
          List<dynamic> list = jsonDecode(jsonString);
          return list.map((colorValue) => Color(colorValue as int)).toList();
        }).toList();
      });
    } else {
      setState(() {
        answerTextColor = [];
      });
    }
  }


  @override
  Widget build(BuildContext context) {
    Sizes.initialize(context);
    //print(answers);

    return Scaffold(
      body: SafeArea(
        child: Column(
          children: [
            Padding(
              padding: EdgeInsets.all(Sizes.paddingBig),
              child: Column(
                children: [
                  Align(
                    alignment: Alignment.centerLeft,
                    child: GestureDetector(
                      onTap: (){
                        setState(() {
                          if(questionCount > 0){
                            questionCount--;
                          }
                        });
                      },
                      child: Container(
                        margin: EdgeInsets.only(
                            bottom: Sizes.paddingRegular
                        ),
                        width: Sizes.widthPercent * 10,
                        height: Sizes.widthPercent * 10,
                        decoration: BoxDecoration(
                          borderRadius: BorderRadius.circular(100),
                          border: questionCount == 0 ? Border.all(width: 1, color: white) : Border.all(width: 1, color: black),
                        ),
                        child: Icon(
                          Boxicons.bx_arrow_back,
                          color: questionCount == 0 ? white : black,
                        ),
                      ),
                    ),
                  ),
                  Container(
                    width: double.infinity,
                    child: Text(
                      "${questionCount+1}.Frage",
                      style: TextStyle(
                        fontFamily: font,
                        fontSize: fontSizeBig,
                      ),
                    ),
                  ),
                  Padding(
                    padding: EdgeInsets.only(
                      top: Sizes.paddingRegular
                    ),
                    child: Text(
                      questions[questionCount]["question"],
                      textAlign: TextAlign.center,
                      style: TextStyle(
                          fontFamily: font,
                          fontSize: fontSizeRegular
                      ),
                    ),
                  ),
                  Padding(
                    padding: EdgeInsets.only(
                      top: Sizes.paddingRegular
                    ),
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        GestureDetector(
                          onTap: (){
                            setState(() {
                              answers[questionCount][0] = !answers[questionCount][0]!;
                              answers[questionCount][1] = false;
                              answers[questionCount][2] = false;
                              answers[questionCount][3] = false;
                              //print(answers);

                              if (answerBoxColor[questionCount][0] == white) {
                                answerBoxColor[questionCount] = [green80, white, white, white];
                                answerTextColor[questionCount] = [white, green, green, green];
                              }else {
                                answerBoxColor[questionCount] = [white, white, white, white];
                                answerTextColor[questionCount] = [green, green, green, green];
                              }
                            });
                          },
                          child: Container(
                            width: Sizes.widthPercent * 65,
                            height: Sizes.heightPercent * 6,
                            decoration: BoxDecoration(
                                color: answerBoxColor[questionCount][0],
                                borderRadius: BorderRadius.circular(Sizes.borderRadius),
                                border: Border.all(
                                    color: green
                                )
                            ),
                            child: Center(
                              child: Text(
                                questions[questionCount]["answers"][0],
                                style: TextStyle(
                                  color: answerTextColor[questionCount][0],
                                  fontFamily: font,
                                  fontSize: fontSizeSmall,
                                ),
                              ),
                            ),
                          ),
                        ),
                        GestureDetector(
                          onTap: (){
                            setState(() {
                              answers[questionCount][0] = false;
                              answers[questionCount][1] = !answers[questionCount][1]!;
                              answers[questionCount][2] = false;
                              answers[questionCount][3] = false;
                              //print(answers);

                              if (answerBoxColor[questionCount][1] == white) {
                                answerBoxColor[questionCount] = [white, green80, white, white];
                                answerTextColor[questionCount] = [green, white, green, green];
                              }else {
                                answerBoxColor[questionCount] = [white, white, white, white];
                                answerTextColor[questionCount] = [green, green, green, green];
                              }
                            });
                          },
                          child: Container(
                            margin: EdgeInsets.only(
                                top: Sizes.paddingSmall
                            ),
                            width: Sizes.widthPercent * 65,
                            height: Sizes.heightPercent * 6,
                            decoration: BoxDecoration(
                                color: answerBoxColor[questionCount][1],
                                borderRadius: BorderRadius.circular(Sizes.borderRadius),
                                border: Border.all(
                                    color: green
                                )
                            ),
                            child: Center(
                              child: Text(
                                questions[questionCount]["answers"][1],
                                style: TextStyle(
                                  color: answerTextColor[questionCount][1],
                                  fontFamily: font,
                                  fontSize: fontSizeSmall,
                                ),
                              ),
                            ),
                          ),
                        ),
                        GestureDetector(
                          onTap: (){
                            setState(() {
                              answers[questionCount][0] = false;
                              answers[questionCount][1] = false;
                              answers[questionCount][2] = !answers[questionCount][2]!;
                              answers[questionCount][3] = false;
                              //print(answers);

                              if (answerBoxColor[questionCount][2] == white) {
                                answerBoxColor[questionCount] = [white, white, green80, white];
                                answerTextColor[questionCount] = [green, green, white, green];
                              }else {
                                answerBoxColor[questionCount] = [white, white, white, white];
                                answerTextColor[questionCount] = [green, green, green, green];
                              }
                            });
                          },
                          child: Container(
                            margin: EdgeInsets.only(
                                top: Sizes.paddingSmall
                            ),
                            width: Sizes.widthPercent * 65,
                            height: Sizes.heightPercent * 6,
                            decoration: BoxDecoration(
                                color: answerBoxColor[questionCount][2],
                                borderRadius: BorderRadius.circular(Sizes.borderRadius),
                                border: Border.all(
                                    color: green
                                )
                            ),
                            child: Center(
                              child: Text(
                                questions[questionCount]["answers"][2],
                                style: TextStyle(
                                  color: answerTextColor[questionCount][2],
                                  fontFamily: font,
                                  fontSize: fontSizeSmall,
                                ),
                              ),
                            ),
                          ),
                        ),
                        GestureDetector(
                          onTap: (){
                            setState(() {
                              answers[questionCount][0] = false;
                              answers[questionCount][1] = false;
                              answers[questionCount][2] = false;
                              answers[questionCount][3] = !answers[questionCount][3]!;
                              //print(answers);

                              if (answerBoxColor[questionCount][3] == white) {
                                answerBoxColor[questionCount] = [white, white, white, green80];
                                answerTextColor[questionCount] = [green, green, green, white];
                              }else {
                                answerBoxColor[questionCount] = [white, white, white, white];
                                answerTextColor[questionCount] = [green, green, green, green];
                              }
                            });
                          },
                          child: Container(
                            margin: EdgeInsets.only(
                                top: Sizes.paddingSmall
                            ),
                            width: Sizes.widthPercent * 65,
                            height: Sizes.heightPercent * 6,
                            decoration: BoxDecoration(
                                color: answerBoxColor[questionCount][3],
                                borderRadius: BorderRadius.circular(Sizes.borderRadius),
                                border: Border.all(
                                    color: green
                                )
                            ),
                            child: Center(
                              child: Text(
                                questions[questionCount]["answers"][3],
                                style: TextStyle(
                                  color: answerTextColor[questionCount][3],
                                  fontFamily: font,
                                  fontSize: fontSizeSmall,
                                ),
                              ),
                            ),
                          ),
                        )
                      ],
                    ),
                  )
                ],
              ),
            ),
            GestureDetector(
              onTapDown: (_) {
                setState(() {
                  _isPressed = true;
                });
              },
              onTapUp: (_) {
                setState(() {
                  _isPressed = false;
                  if(answers[questionCount][0]! || answers[questionCount][1]! ||
                      answers[questionCount][2]! || answers[questionCount][3]!){
                    if (questionCount < questions.length - 1) {
                      if(answers.length <= questionCount + 1){
                        answers.add({
                          0 : false,
                          1 : false,
                          2 : false,
                          3 : false
                        });
                        answerBoxColor.add([white, white, white, white]);
                        answerTextColor.add([green, green, green, green]);

                        //answerBoxColor[questionCount] = [white, white, white, white];
                        //answerTextColor[questionCount] = [green, green, green, green];

                        questionCount++;
                        //print(answers);
                      }else{
                        questionCount++;
                        //print(answers);
                      }
                    }else{
                      //print("to homepage");
                      //print(answers);

                      saveProfileData(answers, answerBoxColor, answerTextColor);

                      Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (context) => MainPage()));
                    }
                  }
                });
              },
              onTapCancel: () {
                setState(() {
                  _isPressed = false;
                });
              },
              child: AnimatedContainer(
                duration: Duration(milliseconds: 200),
                width: 200,
                padding: EdgeInsets.all(Sizes.paddingSmall),
                margin: EdgeInsets.only(top: Sizes.paddingBig),
                decoration: BoxDecoration(
                  color: _isPressed ? green.withOpacity(0.8) : green,
                  borderRadius: BorderRadius.circular(Sizes.borderRadius),
                ),
                child: Center(
                  child: Text(
                    "nächste",
                    style: TextStyle(
                      color: white,
                      fontFamily: font,
                      fontSize: fontSizeSmall,
                    ),
                  ),
                ),
              ),
            ),
          ],
        ),
      )
    );
  }
}
