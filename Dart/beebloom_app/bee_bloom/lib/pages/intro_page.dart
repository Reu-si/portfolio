import 'package:bee_bloom/pages/survey_page.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/constants/sizes.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'dart:convert';


class IntroPage extends StatefulWidget {
  const IntroPage({super.key});

  @override
  State<IntroPage> createState() => _IntroPageState();
}

class _IntroPageState extends State<IntroPage> {
  bool _isPressed = false;

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

  @override
  Widget build(BuildContext context) {
    Sizes.initialize(context);

    return Scaffold(
      body: SafeArea(
        child: Padding(
          padding: EdgeInsets.all(Sizes.paddingBig),
          child: Center(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Text(
                  "Bitte beantworte zu Beginn die folgenden Fragen..",
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontFamily: font,
                    fontSize: fontSizeSmall,
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
                      _navigateToSurveyPage(context);
                    });
                  },
                  onTapCancel: () {
                    setState(() {
                      _isPressed = false;
                    });
                  },
                  child: AnimatedContainer(
                    duration: Duration(milliseconds: 200),
                    width: 200, // Feste Breite für den Container
                    padding: EdgeInsets.all(Sizes.paddingSmall),
                    margin: EdgeInsets.only(top: Sizes.paddingBig),
                    decoration: BoxDecoration(
                      color: _isPressed ? green.withOpacity(0.8) : green,
                      borderRadius: BorderRadius.circular(Sizes.borderRadius),
                    ),
                    child: Center(
                      child: Text(
                        "Los gehts",
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
          ),
        ),
      ),
    );
  }

  void _navigateToSurveyPage(BuildContext context) async {
    SharedPreferences prefs = await SharedPreferences.getInstance();
    await prefs.setBool('isFirstLaunch', false);

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

    saveProfileData(answers, answerBoxColor, answerTextColor);

    Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => SurveyPage(),
      ),
    );
  }
}