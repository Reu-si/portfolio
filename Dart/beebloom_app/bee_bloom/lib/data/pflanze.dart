
import 'dart:ui';

class Pflanze  {
  String name;
  bool invasiv;
  String heimisch;
  String artenvielfalt;
  String bildpfad;
  String bedroht;
  String sonne;
  String trocken;
  String pflege;
  String giftig;
  String aussaat;
  int wateringCycle; // in days
  DateTime lastWatered;
  int fertilizingCycle;
  DateTime lastfertilized;

  Pflanze ({
    required this.wateringCycle, required this.lastWatered, required this.aussaat,
    required this.bedroht, required this.giftig, required this.invasiv,
    required this.pflege, required this.sonne, required this.artenvielfalt,
    required this.trocken, required this.bildpfad, required this.name,
    required this.heimisch, required this.fertilizingCycle, required this.lastfertilized,
  });
  String toString() {
    return '$name';
  }

  Pflanze clone() {
    return Pflanze(
      name:name,
      invasiv: invasiv,
      heimisch:heimisch,
      artenvielfalt: artenvielfalt,
      bildpfad:bildpfad,
      bedroht:bedroht,
      sonne:sonne,
      trocken:trocken,
      pflege:pflege,
      giftig: giftig,
      aussaat: aussaat,
      wateringCycle:wateringCycle, // in days
      lastWatered:lastWatered,
      fertilizingCycle:fertilizingCycle,
      lastfertilized:lastfertilized,
    );
  }

  factory Pflanze.fromJson(Map<String, dynamic> json) {
    return Pflanze(
      name: json['name'],
      invasiv: json['invasiv'],
      heimisch: json['heimisch'],
      artenvielfalt: json['artenvielfalt'],
      bildpfad: json['bildpfad'],
      bedroht: json['bedroht'],
      sonne: json['sonne'],
      trocken: json['trocken'],
      pflege: json['pflege'],
      giftig: json['giftig'],
      aussaat: json['aussaat'],
      wateringCycle: json['wateringCycle'],
      lastWatered: DateTime.parse(json['lastWatered']),
      fertilizingCycle: json['fertilizingCycle'],
      lastfertilized: DateTime.parse(json['lastfertilized']),
    );
  }

  Map<String, dynamic> toJson() {
    return {
      'name': name,
      'invasiv': invasiv,
      'heimisch': heimisch,
      'artenvielfalt': artenvielfalt,
      'bildpfad': bildpfad,
      'bedroht': bedroht,
      'sonne': sonne,
      'trocken': trocken,
      'pflege': pflege,
      'giftig': giftig,
      'aussaat': aussaat,
      'wateringCycle': wateringCycle,
      'lastWatered': lastWatered.toIso8601String(),
      'fertilizingCycle': fertilizingCycle,
      'lastfertilized': lastfertilized.toIso8601String(),
    };
  }
}