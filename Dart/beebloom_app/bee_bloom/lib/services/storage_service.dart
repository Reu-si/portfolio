import 'dart:convert';

import 'package:bee_bloom/data/pflanze.dart';
import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';

class StorageService{
static String PinboardKey = 'Pinboard';
static String PlantKeyPrefix = 'Plant_';
static String WaterKey = "Watered";
static String FertilizeKey = "Fertilized";
static String RainyKey = "Rain";
static const String UserLevelKey = "UserLevel";
static const String WaterStreakKey = "WaterStreak";


  static Future<void> addPinBoard(String PinboardName) async{
    if(PinboardName.contains(".") || PinboardName == "Wishlist" || PinboardName == ""){
      return;
    }
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<String> savedPinboards = await getAllPinBoards();
    savedPinboards.add(PinboardName);
    await prefs.setStringList(PinboardKey, savedPinboards);
  }

  static Future<List<String>> getAllPinBoards() async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    final List<String> PinboardNames = prefs.getStringList(PinboardKey) ?? [];
    return PinboardNames;
  }

  static Future<void> deletePinBoard(String PinboardName) async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<String> savedPinboards = await getAllPinBoards();
    savedPinboards.remove(PinboardName);
    await prefs.setStringList(PinboardKey, savedPinboards);
  }

  static Future<void> addPlant(String Plantname, String pinBoardName) async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<String> savedPlants = await getAllPlantsinPinboard(pinBoardName);
    if(Plantname.contains(".") || savedPlants.contains(pinBoardName + "." + Plantname)){ // muss noch Bedingung geben, dass keine Pflanze mehrmals drin sein darf
      return;
    }
    savedPlants.add(pinBoardName + "." + Plantname);
    await prefs.setStringList(PlantKeyPrefix + pinBoardName, savedPlants);
  }

  static Future<void> deletePlantfromPinboard(String PlantName, String PinboardName) async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<String> AllPlantsinPinboard = await getAllPlantsinPinboard(PinboardName);
    AllPlantsinPinboard.remove(PinboardName + "." + PlantName);
    print("WURDE PFLANZE GELÖSCHT");
    print(AllPlantsinPinboard);
    await prefs.setStringList(PlantKeyPrefix + PinboardName, AllPlantsinPinboard);
  }

  static Future<List<String>> getAllPlantsinPinboard(String pinBoardName) async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    final List<String> PlantNames = prefs.getStringList(PlantKeyPrefix + pinBoardName) ?? [];
    List<String> AllPlantsinPinboard = [];
    for(int i = 0; i < PlantNames.length; i++){
      String currentName = PlantNames[i];
      String PlantPinboard = currentName.split('.')[0];

      if (PlantPinboard == pinBoardName){
        AllPlantsinPinboard.add(currentName);
      }
    }
    return AllPlantsinPinboard;
  }

  static Future<List<DateTime>> getAllWateredDays() async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<String> wateredDays = prefs.getStringList(WaterKey) ?? [];
    List<DateTime> result = [];
    for(int i = 0; i < wateredDays.length; i++){
      DateTime d = DateUtils.dateOnly(DateTime.fromMillisecondsSinceEpoch(int.parse(wateredDays[i])));
      result.add(d);
    }

    return result;
  }

  static Future<void> addWateredDay(DateTime wateredDay) async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<DateTime> days = await getAllWateredDays();
    days.add(wateredDay);

    List<String> results = [];
    for(int i = 0; i < days.length; i++){
      results.add(days[i].millisecondsSinceEpoch.toString());
    }

    await prefs.setStringList(WaterKey, results);
  }

  static Future<void> removeWateredDay(DateTime wateredDay) async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<DateTime> days = await getAllWateredDays();
    days.remove(wateredDay);

    List<String> results = [];
    for(int i = 0; i < days.length; i++){
      results.add(days[i].millisecondsSinceEpoch.toString());
    }

    await prefs.setStringList(WaterKey, results);
  }

static Future<List<DateTime>> getAllRainyDays() async{
  SharedPreferences prefs = await SharedPreferences.getInstance();
  List<String> wateredDays = prefs.getStringList(RainyKey) ?? [];
  List<DateTime> result = [];
  for(int i = 0; i < wateredDays.length; i++){
    DateTime d = DateUtils.dateOnly(DateTime.fromMillisecondsSinceEpoch(int.parse(wateredDays[i])));

    result.add(d);
  }

  return result;
}

static Future<void> addRainyDay(DateTime wateredDay) async{
  SharedPreferences prefs = await SharedPreferences.getInstance();
  List<DateTime> days = await getAllWateredDays();
  days.add(wateredDay);

  List<String> results = [];
  for(int i = 0; i < days.length; i++){
    results.add(days[i].millisecondsSinceEpoch.toString());
  }

  await prefs.setStringList(RainyKey, results);
}

static Future<void> removeRainyDay(DateTime wateredDay) async{
  SharedPreferences prefs = await SharedPreferences.getInstance();
  List<DateTime> days = await getAllWateredDays();
  days.remove(wateredDay);

  List<String> results = [];
  for(int i = 0; i < days.length; i++){
    results.add(days[i].millisecondsSinceEpoch.toString());
  }

  await prefs.setStringList(RainyKey, results);
}

  static Future<List<DateTime>> getAllFertilizedDays() async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<String> fertilizedDays = prefs.getStringList(FertilizeKey) ?? [];
    List<DateTime> result = [];
    for(int i = 0; i < fertilizedDays.length; i++){
      DateTime d = DateUtils.dateOnly(DateTime.fromMillisecondsSinceEpoch(int.parse(fertilizedDays[i])));
      result.add(d);
    }

    return result;
  }

  static Future<void> addFertilizedDay(DateTime fertilizedDay) async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<DateTime> days = await getAllFertilizedDays();
    days.add(fertilizedDay);

    List<String> results = [];
    for(int i = 0; i < days.length; i++){
      results.add(days[i].millisecondsSinceEpoch.toString());
    }

    await prefs.setStringList(FertilizeKey, results);
  }

static Future<void> removeFertilizedDay(DateTime fertilizedDay) async{
  SharedPreferences prefs = await SharedPreferences.getInstance();
  List<DateTime> days = await getAllFertilizedDays();
  days.remove(fertilizedDay);

  List<String> results = [];
  for(int i = 0; i < days.length; i++){
    results.add(days[i].millisecondsSinceEpoch.toString());
  }

  await prefs.setStringList(FertilizeKey, results);
}
// functions for saving and retrieving water streaks
static Future<void> saveWaterStreak(int streak) async {
  SharedPreferences prefs = await SharedPreferences.getInstance();
  await prefs.setInt(WaterStreakKey, streak);
}

static Future<int> getWaterStreak() async {
  SharedPreferences prefs = await SharedPreferences.getInstance();
  return prefs.getInt(WaterStreakKey) ?? 0; // Default streak is 0
}

  // Function to calculate and retrieve user level based on number of plants
  static Future<int> getUserLevel() async {
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<String> pinboards = await getAllPinBoards();
    int totalPlants = 0;
    for (String pinboard in pinboards) {
      List<String> plants = await getAllPlantsinPinboard(pinboard);
      totalPlants += plants.length;
    }
    return (totalPlants / 1.3).floor().clamp(1, double.infinity).toInt(); // User level is the total number of plants divided by 5
  }

  static Future<void> savePlant(Pflanze pflanze) async {
    SharedPreferences prefs = await SharedPreferences.getInstance();
    String plantKey = 'plant_${pflanze.name}';
    String plantJson = jsonEncode(pflanze.toJson());
    await prefs.setString(plantKey, plantJson);
  }
}