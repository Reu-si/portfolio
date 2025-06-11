import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/constants/sizes.dart';
import 'package:bee_bloom/data/pflanze.dart';
import 'package:bee_bloom/data/pflanzendaten.dart';
import 'package:bee_bloom/pages/plant_profile_page.dart';
import 'package:bee_bloom/services/storage_service.dart';
import 'package:flutter/material.dart';
import 'package:flutter/cupertino.dart';
import 'package:table_calendar/table_calendar.dart';

class CalendarPage extends StatefulWidget {
  const CalendarPage({super.key});

  @override
  State<CalendarPage> createState() => _CalendarPageState();
}

class _CalendarPageState extends State<CalendarPage> {
  Map<DateTime, List<Map<String, dynamic>>> _events = {}; // Updated to store event details
  List<DateTime> wateredDays = [];
  List<DateTime> fertilizedDays = [];
  List<DateTime> rainyDays = [];
  List<Map<String, dynamic>> _selectedEvents = [];
  CalendarFormat _calendarFormat = CalendarFormat.month;
  DateTime _focusedDay = DateTime.now();
  DateTime _selectedDay = DateTime.now();
  int waterStreak = 0;
  List<String> AllPinboards = [];
  List<Pflanze> AllPlantsinPinboards = [];
  List<String> plantsWithPinboards = [];
  Map<String, List<Pflanze>> mapOfPlantNamesWithPinboards = {};
  List<String> wateringImagePaths = [];
  List<String> fertilizingImagePaths = [];

  @override
  void initState() {
    super.initState();
    fetchInitialData();
  }

  void fetchInitialData() async {
    List<String> result = await StorageService.getAllPinBoards();
    AllPinboards = result;
    for (String pinboard in AllPinboards) {
      List<String> ergebnis = await StorageService.getAllPlantsinPinboard(pinboard);
      plantsWithPinboards.addAll(ergebnis);
      for (String plantEntry in ergebnis) {
        String pinboardName = plantEntry.split('.')[0];
        String plantName = plantEntry.split('.')[1];
        Pflanze pflanze = pflanzen.firstWhere((element) => element.name == plantName);
        if (!mapOfPlantNamesWithPinboards.containsKey(pinboardName)) {
          mapOfPlantNamesWithPinboards[pinboardName] = [];
        }
        mapOfPlantNamesWithPinboards[pinboardName]!.add(pflanze);
      }
    }
    waterStreak = await StorageService.getWaterStreak();
    await loadData();
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: EdgeInsets.all(Sizes.paddingSmall),
      child: Column(
        children: [
          Container(
            padding: EdgeInsets.all(Sizes.paddingRegular),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                _buildIconColumn('\nRegen', rainyDays, (day) async {
                  DateTime normalizedSelectedDay = normalizeDate(_selectedDay);
                  if (rainyDays.contains(day)) {
                    await StorageService.removeRainyDay(day);
                    await updatePlantWateredDates(normalizedSelectedDay, subtract: true);
                    await addPastEvents(normalizedSelectedDay, isWatering: true);
                  } else {
                    await StorageService.addRainyDay(day);
                    await updatePlantWateredDates(normalizedSelectedDay);
                    clearPastEvents(normalizedSelectedDay, isWatering: true);
                  }
                  await loadData();
                }),
                _buildIconColumn('Heute\ngegossen', wateredDays, (day) async {
                  DateTime normalizedSelectedDay = normalizeDate(_selectedDay);
                  if (wateredDays.contains(day)) {
                    await StorageService.removeWateredDay(day);
                    setState(() {
                      wateredDays.removeWhere((day) => normalizeDate(day) == normalizedSelectedDay);
                      if (waterStreak > 0) waterStreak--; // Decrease water streak if removing watered day
                      StorageService.saveWaterStreak(waterStreak);
                    });
                    // Revert the lastWatered property
                    await updatePlantWateredDates(normalizedSelectedDay, subtract: true);
                    await addPastEvents(normalizedSelectedDay, isWatering: true);
                  } else {
                    await StorageService.addWateredDay(day);
                    wateredDays.add(normalizedSelectedDay);
                    waterStreak++; // Increase water streak if adding watered day
                    StorageService.saveWaterStreak(waterStreak);
                    // Update the lastWatered property
                    await updatePlantWateredDates(normalizedSelectedDay);
                    clearPastEvents(normalizedSelectedDay, isWatering: true);
                  }
                  await loadData();
                }),
                _buildIconColumn('\nGedüngt', fertilizedDays, (day) async {
                  DateTime normalizedSelectedDay = normalizeDate(_selectedDay);
                  if (fertilizedDays.contains(day)) {
                    await StorageService.removeFertilizedDay(day);
                    // Revert the lastfertilized property
                    await updatePlantFertilizedDates(normalizedSelectedDay, subtract: true);
                    await addPastEvents(normalizedSelectedDay, isFertilizing: true);
                  } else {
                    await StorageService.addFertilizedDay(day);
                    // Update the lastWatered property
                    await updatePlantFertilizedDates(normalizedSelectedDay);
                    clearPastEvents(normalizedSelectedDay, isFertilizing: true);
                  }
                  await loadData();
                }),
              ],
            ),
          ),
          TableCalendar(
            firstDay: DateTime.utc(2010, 10, 16),
            lastDay: DateTime.utc(2030, 3, 14),
            focusedDay: _focusedDay,
            selectedDayPredicate: (day) {
              return isSameDay(_selectedDay, day);
            },
            onDaySelected: _onDaySelected,
            calendarFormat: _calendarFormat,
            onFormatChanged: (format) {
              setState(() {
                _calendarFormat = format;
              });
            },
            onPageChanged: (focusedDay) {
              _focusedDay = focusedDay;
            },
            startingDayOfWeek: StartingDayOfWeek.monday,
            calendarStyle: CalendarStyle(
              selectedDecoration: BoxDecoration(
                color: green,
                shape: BoxShape.circle,
              ),
              todayDecoration: BoxDecoration(
                color: lightgreen,
                shape: BoxShape.circle,
              ),
              defaultTextStyle: TextStyle(
                color: black,
              ),
              weekendTextStyle: TextStyle(
                color: green,
              ),
            ),
            calendarBuilders: CalendarBuilders(
              markerBuilder: (context, date, events) {
                if (events.isEmpty) return SizedBox();
                List<Widget> markers = [];
                for (var event in events) {
                  if (event is Map<String, dynamic>) {
                    Color markerColor;
                    if (event['eventType'] == 'watering') {
                      markerColor = lightblue; // Watering event
                    } else if (event['eventType'] == 'fertilizing') {
                      markerColor = yellow; // Fertilizing event
                    } else {
                      markerColor = lightgrey; // Default color for other events
                    }
                    markers.add(_buildMarker(markerColor));
                  }
                }
                return Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: markers,
                );
              },
            ),
            eventLoader: (day) {
              return _events[normalizeDate(day)] ?? [];
            },
          ),
          const SizedBox(height: 8.0),
          Expanded(
            child: ListView.builder(
              itemCount: _selectedEvents.length,
              itemBuilder: (context, index) {
                return _buildEventTile(_selectedEvents[index]);
              },
            ),
          ),
        ],
      ),
    );
  }

  Column _buildIconColumn(String title, List<DateTime> eventDays, Function(DateTime) onTap) {
    bool isFutureDay = false;
    Color iconColor = lightblue;

    if (title == "\nGedüngt") {
      iconColor = yellow;
    }
    // Check if the selected day is in the future
    DateTime normalizedSelectedDay = normalizeDate(_selectedDay);
    isFutureDay = normalizedSelectedDay.isAfter(DateTime.now());

    return Column(
      children: [
        Padding(
          padding: const EdgeInsets.all(8.0),
          child: Text(
            title,
            textAlign: TextAlign.center,
            style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
          ),
        ),
        GestureDetector(
          onTap: isFutureDay
              ? null
              : () => onTap(normalizedSelectedDay), // Disable onTap if it's a future day
          child: Icon(
            eventDays.map(normalizeDate).contains(normalizeDate(_selectedDay))
                ? CupertinoIcons.checkmark_alt_circle_fill
                : CupertinoIcons.plus_circle,
            size: 40,
            color: eventDays.map(normalizeDate).contains(normalizeDate(_selectedDay))
                ? iconColor
                : black,
          ),
        ),
      ],
    );
  }

  Future<void> loadData() async {
    wateredDays = await StorageService.getAllWateredDays();
    fertilizedDays = await StorageService.getAllFertilizedDays();
    rainyDays = await StorageService.getAllRainyDays();

    _events = {};
    DateTime startOfMonth = DateTime(_selectedDay.year, _selectedDay.month, 1);
    DateTime endOfMonth = DateTime(_selectedDay.year, _selectedDay.month + 1, 0);

    mapOfPlantNamesWithPinboards.forEach((pinboardName, plants) {
      Map<String, List<String>> wateringEvents = {};
      Map<String, List<String>> fertilizingEvents = {};

      for (var pflanze in plants) {
        List<DateTime> wateringDates = calculateWateringDates(pflanze, startOfMonth, endOfMonth);
        List<DateTime> fertilizingDates = calculateFertilizingDates(pflanze, startOfMonth, endOfMonth);

        for (var day in wateringDates) {
          final normalizedDay = normalizeDate(day);
          wateringEvents[normalizedDay.toString()] ??= [];
          wateringEvents[normalizedDay.toString()]!.add(pflanze.bildpfad);
        }

        for (var day in fertilizingDates) {
          final normalizedDay = normalizeDate(day);
          fertilizingEvents[normalizedDay.toString()] ??= [];
          fertilizingEvents[normalizedDay.toString()]!.add(pflanze.bildpfad);
        }
      }

      wateringEvents.forEach((day, imagePaths) {
        final normalizedDay = DateTime.parse(day);
        _events[normalizedDay] ??= [];
        _events[normalizedDay]!.add({
          'pinboardName': pinboardName,
          'eventType': 'watering',
          'imagePaths': imagePaths,
          'plantNames': plants.where((p) => imagePaths.contains(p.bildpfad)).map((p) => p.name).toList(), // Add plant names
        });
      });

      fertilizingEvents.forEach((day, imagePaths) {
        final normalizedDay = DateTime.parse(day);
        _events[normalizedDay] ??= [];
        _events[normalizedDay]!.add({
          'pinboardName': pinboardName,
          'eventType': 'fertilizing',
          'imagePaths': imagePaths,
          'plantNames': plants.where((p) => imagePaths.contains(p.bildpfad)).map((p) => p.name).toList(), // Add plant names
        });
      });
    });

    // Remove past watered and fertilized days
    for (var day in wateredDays) {
      final normalizedDay = normalizeDate(day);
      _events[normalizedDay]?.removeWhere((event) => event['eventType'] == 'watering');
    }
    for (var day in fertilizedDays) {
      final normalizedDay = normalizeDate(day);
      _events[normalizedDay]?.removeWhere((event) => event['eventType'] == 'fertilizing');
    }
    for (var day in rainyDays) {
      final normalizedDay = normalizeDate(day);
      _events[normalizedDay]?.removeWhere((event) => event['eventType'] == 'rainy');
    }

    _selectedEvents = _getEventsForDay(_selectedDay);
    setState(() {});
  }

  List<Map<String, dynamic>> _getEventsForDay(DateTime day) {
    return _events[normalizeDate(day)] ?? [];
  }

  void _onDaySelected(DateTime selectedDay, DateTime focusedDay) {
    if (!isSameDay(_selectedDay, selectedDay)) {
      setState(() {
        _selectedDay = selectedDay;
        _focusedDay = focusedDay;
        _selectedEvents = _getEventsForDay(selectedDay);
      });
    }
  }

  DateTime normalizeDate(DateTime date) {
    return DateTime(date.year, date.month, date.day);
  }

  Future<void> updatePlantWateredDates(DateTime date, {bool subtract = false}) async {
    for (var plants in mapOfPlantNamesWithPinboards.values) {
      for (var pflanze in plants) {
        if (_events[normalizeDate(date)]?.any((event) => event['imagePaths'].contains(pflanze.bildpfad)) ?? false) {
          if (subtract) {
            pflanze.lastWatered = pflanze.lastWatered.subtract(Duration(days: pflanze.wateringCycle));
          } else {
            pflanze.lastWatered = date;
          }
          await StorageService.savePlant(pflanze);
        }
      }
    }
  }

  Future<void> updatePlantFertilizedDates(DateTime date, {bool subtract = false}) async {
    for (var plants in mapOfPlantNamesWithPinboards.values) {
      for (var pflanze in plants) {
        if (_events[normalizeDate(date)]?.any((event) => event['imagePaths'].contains(pflanze.bildpfad)) ?? false) {
          if (subtract) {
            pflanze.lastfertilized = pflanze.lastfertilized.subtract(Duration(days: pflanze.fertilizingCycle));
          } else {
            pflanze.lastfertilized = date;
          }
          await StorageService.savePlant(pflanze);
        }
      }
    }
  }

  void clearPastEvents(DateTime date, {bool isWatering = false, bool isFertilizing = false}) {
    for (var plants in mapOfPlantNamesWithPinboards.values) {
      for (var pflanze in plants) {
        if (isWatering) {
          // Clear watering events before the selected day
          List<DateTime> wateringDates = calculateWateringDates(pflanze, DateTime(2024), date);
          for (var day in wateringDates) {
            final normalizedDay = normalizeDate(day);
            _events[normalizedDay]?.removeWhere((event) => event['eventType'] == 'watering');
            if (_events[normalizedDay]?.isEmpty ?? false) {
              _events.remove(normalizedDay);
            }
          }
        } else if (isFertilizing) {
          // Clear fertilizing events before the selected day
          List<DateTime> fertilizingDates = calculateFertilizingDates(pflanze, DateTime(2024), date);
          for (var day in fertilizingDates) {
            final normalizedDay = normalizeDate(day);
            _events[normalizedDay]?.removeWhere((event) => event['eventType'] == 'fertilizing');
            if (_events[normalizedDay]?.isEmpty ?? false) {
              _events.remove(normalizedDay);
            }
          }
        }
      }
    }
  }

  Future<void> addPastEvents(DateTime date, {bool isWatering = false, bool isFertilizing = false}) async {
    for (var plants in mapOfPlantNamesWithPinboards.values) {
      for (var pflanze in plants) {
        if (isWatering) {
          // Re-add watering events before the selected day
          List<DateTime> wateringDates = calculateWateringDates(pflanze, DateTime(2024), date);
          for (var day in wateringDates) {
            final normalizedDay = normalizeDate(day);
            if (_events[normalizedDay]?.any((event) => event['imagePaths'].contains(pflanze.bildpfad)) ?? false) {
              continue; // Skip if event already exists
            }
            _events[normalizedDay] ??= [];
            _events[normalizedDay]!.add({
              'pinboardName': pflanze.name,
              'eventType': 'watering',
              'imagePaths': [pflanze.bildpfad],
              'plantNames': [pflanze.name], // Add plant name
            });
          }
        } else if (isFertilizing) {
          // Re-add fertilizing events before the selected day
          List<DateTime> fertilizingDates = calculateFertilizingDates(pflanze, DateTime(2024), date);
          for (var day in fertilizingDates) {
            final normalizedDay = normalizeDate(day);
            if (_events[normalizedDay]?.any((event) => event['imagePaths'].contains(pflanze.bildpfad)) ?? false) {
              continue; // Skip if event already exists
            }
            _events[normalizedDay] ??= [];
            _events[normalizedDay]!.add({
              'pinboardName': pflanze.name,
              'eventType': 'fertilizing',
              'imagePaths': [pflanze.bildpfad],
              'plantNames': [pflanze.name], // Add plant name
            });
          }
        }
      }
    }
  }

  Widget _buildEventTile(Map<String, dynamic> event) {
    return ListTile(
      leading: Text(event['pinboardName']!),
      title: Row(
        children: [
          Icon(
            event['eventType'] == 'watering' ? CupertinoIcons.drop_fill : CupertinoIcons.circle_grid_hex_fill,
            color: event['eventType'] == 'watering' ? lightblue : yellow,
          ),
          SizedBox(width: 8), // Add some spacing
          Expanded(
            child: Row(
              children: (event['imagePaths'] as List<String>).asMap().entries.map((entry) {
                int index = entry.key;
                String imagePath = entry.value;
                String plantName = (event['plantNames'] as List<String>)[index]; // Get corresponding plant name
                return Padding(
                  padding: const EdgeInsets.symmetric(horizontal: 2.0),
                  child: GestureDetector(
                    onTap: () {
                      Navigator.push(
                        context,
                        MaterialPageRoute(
                          builder: (context) => PlantProfilePage(title: plantName), // Pass plant name
                        ),
                      );
                    },
                    child: ClipRRect(
                      borderRadius: BorderRadius.circular(5.0),
                      child: Image.asset(
                        imagePath,
                        height: 50,
                        width: 50,
                        fit: BoxFit.cover,
                      ),
                    ),
                  ),
                );
              }).toList(),
            ),
          ),
        ],
      ),
    );
  }
}

Widget _buildMarker(Color markerColor) {
  return Container(
    margin: const EdgeInsets.symmetric(horizontal: 1.5),
    width: 7.0,
    height: 7.0,
    decoration: BoxDecoration(
      shape: BoxShape.circle,
      color: markerColor,
    ),
  );
}

List<DateTime> calculateWateringDates(Pflanze pflanze, DateTime start, DateTime end) {
  List<DateTime> wateringDates = [];
  DateTime nextWateringDate = pflanze.lastWatered.add(Duration(days: pflanze.wateringCycle));

  while (nextWateringDate.isBefore(end)) {
    if (nextWateringDate.isAfter(start) || nextWateringDate.isAtSameMomentAs(start)) {
      wateringDates.add(nextWateringDate);
    }
    nextWateringDate = nextWateringDate.add(Duration(days: pflanze.wateringCycle));
  }

  return wateringDates;
}

List<DateTime> calculateFertilizingDates(Pflanze pflanze, DateTime start, DateTime end) {
  List<DateTime> fertilizingDates = [];
  DateTime nextFertilizingDate = pflanze.lastfertilized.add(Duration(days: pflanze.fertilizingCycle));

  while (nextFertilizingDate.isBefore(end)) {
    if (nextFertilizingDate.isAfter(start) || nextFertilizingDate.isAtSameMomentAs(start)) {
      fertilizingDates.add(nextFertilizingDate);
    }
    nextFertilizingDate = nextFertilizingDate.add(Duration(days: pflanze.fertilizingCycle));
  }

  return fertilizingDates;
}
