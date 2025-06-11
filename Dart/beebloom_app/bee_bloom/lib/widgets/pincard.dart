import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/pages/plant_profile_page.dart';
import 'package:flutter/material.dart';

class Pincard extends StatefulWidget {
  String title;
  String imagepath;

  Pincard({super.key, required this.title, required this.imagepath});

  @override
  State<Pincard> createState() => _PincardState();
}

class _PincardState extends State<Pincard> {
  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {
        Navigator.push(
            context,
            MaterialPageRoute(
                builder: (context) => PlantProfilePage(title: widget.title)));
      },
      child: Container(
        margin: EdgeInsets.only(
          left: 20
        ),
        decoration: BoxDecoration(
          borderRadius: BorderRadius.circular(15),
          color: lightgrey,
        ),
        child: Column(
          children: [
            Container(
              child: ClipRRect(
                borderRadius: BorderRadius.only(
                  topLeft: Radius.circular(15),
                  topRight: Radius.circular(15),
                ),
                child: Image(
                  image: AssetImage(widget.imagepath),
                  height: 110,
                  fit: BoxFit.cover,
                  width: 150 ,
                ),
              ),
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Text(widget.title),
            ),
          ],
        ),
      ),
    );
  }
}
