import 'dart:collection';
import 'package:bee_bloom/data/pflanzendaten.dart';
import 'package:bee_bloom/data/pflanze.dart';

class PlantManager {
  final List<Pflanze> plants;
  final LinkedHashMap<DateTime, List<String>> events = LinkedHashMap<DateTime, List<String>>();

  PlantManager(this.plants) {
    _generateEvents();
  }

  // Generates events for all plants
  void _generateEvents() {
    final now = DateTime.now();
    events.clear(); // Clear existing events to avoid duplication

    for (var plant in plants) {
      DateTime nextWateringDay = plant.lastWatered.add(Duration(days: plant.wateringCycle));

      // Generate events for the next two months
      while (nextWateringDay.isBefore(now.add(Duration(days: 60)))) {
        if (!events.containsKey(nextWateringDay)) {
          events[nextWateringDay] = [];
        }
        events[nextWateringDay]!.add('${plant.name} needs watering');
        nextWateringDay = nextWateringDay.add(Duration(days: plant.wateringCycle));
      }
    }
  }

  // Updates the last watered date for a specific plant and regenerates events
  void updateWatering(Pflanze plant) {
    plant.lastWatered = DateTime.now();
    _generateEvents(); // Re-generate events after updating
  }

  // Retrieves events for a specific day
  List<String> getEventsForDay(DateTime day) {
    return events[day] ?? [];
  }

  // Adds a new plant and regenerates events
  void addPlant(Pflanze plant) {
    plants.add(plant);
    _generateEvents();
  }

  // Removes a plant and regenerates events
  void removePlant(Pflanze plant) {
    plants.remove(plant);
    _generateEvents();
  }
}
