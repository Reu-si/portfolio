import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/data/pflanze.dart';
import 'package:bee_bloom/data/pflanzendaten.dart';
import 'package:bee_bloom/data/plant_manager.dart';
import 'package:bee_bloom/services/storage_service.dart';
import 'package:flutter/material.dart';
import 'package:table_calendar/table_calendar.dart';

class Calendar extends StatefulWidget {
  Calendar({super.key});

  @override
  State<Calendar> createState() => _CalendarState();
}

class _CalendarState extends State<Calendar> {
  //late PlantManager plantManager;
  //late List<Pflanze> plants;
  CalendarFormat _calendarFormat = CalendarFormat.month;
  DateTime _focusedDay = DateTime.now();
  DateTime? _selectedDay;

  @override
  void initState() {
    super.initState();
    loadAllPlants();
    //plantManager = PlantManager(plants);
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      child: TableCalendar(
        firstDay: DateTime.utc(2010, 10, 16),
        lastDay: DateTime.utc(2030, 3, 14),
        focusedDay: _focusedDay,
        selectedDayPredicate: (day) {
          return isSameDay(_selectedDay, day);
        },
        onDaySelected: (selectedDay, focusedDay) {
          setState(() {
            _selectedDay = selectedDay;
            _focusedDay = focusedDay;
          });
        },
        calendarFormat: _calendarFormat,
        onFormatChanged: (format) {
          setState(() {
            _calendarFormat = format;
          });
        },
        onPageChanged: (focusedDay) {
          _focusedDay = focusedDay;
        },
        eventLoader: (day) {
          return [];
          //return plantManager.getEventsForDay(day);
        },
      ),
    );
  }

  void loadAllPlants() async{
    List<String> pinBoardNames = await StorageService.getAllPinBoards();
    List<String> savedPlants = [];

    for(int i = 0; i < pinBoardNames.length; i++){
      List<String> newPlants = await StorageService.getAllPlantsinPinboard(pinBoardNames[i]);
      savedPlants.addAll(newPlants);
    }

    List<Pflanze> plants = [];

    for(int i = 0; i < savedPlants.length; i++){
      String plantName = savedPlants[i].split(".")[1];

      for(int j = 0; j < pflanzen.length; j++){
        if(pflanzen[j].name == plantName){
          plants.add(pflanzen[j]);
          break;
        }
      }
    }
  }

}
