import 'dart:ui';
import 'package:bee_bloom/data/pflanzendaten.dart';
import 'package:bee_bloom/services/storage_service.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/widgets/pincard.dart';

import '../data/pflanze.dart';

class Pinboard extends StatefulWidget {
  String pinboardname;
  List <String> pinboardliste;
  VoidCallback add_new_plant;
  VoidCallback deletePinboard;

  Pinboard({super.key, required this.pinboardname, required this.pinboardliste, required this.add_new_plant, required this.deletePinboard});

  @override
  State<Pinboard> createState() => _PinboardState();
}


class _PinboardState extends State<Pinboard> {
  List<Widget> pincards = [];

  @override
  void initState(){
    super.initState();
    StorageService.getAllPlantsinPinboard(widget.pinboardname).then((List<String> result){
      widget.pinboardliste = result;
      for(int i = 0; i < widget.pinboardliste.length; i++){
        String plantName = widget.pinboardliste[i].split('.')[1];
        Pflanze pflanze = pflanzen.firstWhere((element) => element.name == plantName,);
        String path = pflanze.bildpfad;
        pincards.add(Pincard(title: plantName, imagepath: path));
        setState(() {

        });
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Container(
        child: Column(
          children: [
            Container(
              margin: const EdgeInsets.only(
                left: 20,
                top: 20,
                bottom: 20
              ),
              width: double.infinity,
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Text (
                    widget.pinboardname,
                    style: const TextStyle(
                      fontWeight: FontWeight.bold,
                      fontSize: 20,
                    ),
                  ),
                  widget.pinboardname != "Wishlist" ? Padding(
                    padding: EdgeInsets.only(
                      right: 20
                    ),
                    child: PopupMenuButton(
                      child: const Icon(
                        CupertinoIcons.ellipsis_vertical,
                        color: darkgrey,
                      ),
                      onSelected: (value) async{
                        if (value == "delete pinboard"){
                          widget.deletePinboard();
                        }
                      },
                      itemBuilder: (BuildContext context) => <PopupMenuEntry>[
                        PopupMenuItem(
                          value: "delete pinboard",
                          child: Row(
                            children: [
                              Padding(
                                padding: const EdgeInsets.only(right: 8.0),
                                child: Icon(
                                  CupertinoIcons.minus_circle,
                                  color: darkgrey
                                ),
                              ),
                              const Text(
                                'Pinnwand löschen',
                                style: TextStyle(fontSize: 15),
                              ),
                            ],
                          ),
                        ),
                      ]
                    ),
                  ) : const SizedBox()
                ],
              )
            ),
            SingleChildScrollView(
              scrollDirection: Axis.horizontal,
              child: Row(
                children: [
                  ...pincards,
                  GestureDetector(
                    onTap: (){
                      setState(() {
                        widget.add_new_plant();
                      });
                    },
                    child: Container(
                      margin: EdgeInsets.all(20),
                        child: Icon(
                          CupertinoIcons.plus_circle,
                          color: green,
                          //size: 15,
                        )
                    ),
                  )
                ]
              ),
            )
          ],
        )

    );
  }
}
