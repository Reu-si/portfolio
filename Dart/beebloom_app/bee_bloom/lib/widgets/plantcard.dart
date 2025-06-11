import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/pages/plant_profile_page.dart';
import 'package:bee_bloom/services/storage_service.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class Plantcard extends StatefulWidget {
  String title;
  String imageUrl;
  Function()? onTap;

  Plantcard({super.key, required this.title, required this.imageUrl});

  @override
  State<Plantcard> createState() => _PlantcardState();
}

class _PlantcardState extends State<Plantcard> {
  Color buttonColor = green;
  IconData  addIcon = Icons.add;
  List<String> AllPinboards = [];
  Map<String, bool> pinboardStatus = {};

  @override
  void initState() {
    StorageService.getAllPinBoards().then((List<String> result){
      AllPinboards = result;
      _loadPinBoards();
      setState(() {

      });
    });
    super.initState();
  }

  Future<void> _loadPinBoards() async {
    List<String> plantsInWishlist = await StorageService.getAllPlantsinPinboard("Wishlist");
    pinboardStatus['Wishlist'] = plantsInWishlist.contains("Wishlist." + widget.title);
    for (var pinboard in AllPinboards) {
      List<String> plantsInPinboard = await StorageService.getAllPlantsinPinboard(pinboard);
      pinboardStatus[pinboard] = plantsInPinboard.contains(pinboard + "." + widget.title);
    }
    setState(() {});
  }

  Future<void> _togglePlantInPinboard(String pinboardName) async {
    if (pinboardStatus[pinboardName] == true) {
      // Remove from pinboard
      await StorageService.deletePlantfromPinboard(widget.title, pinboardName);
    } else {
      // Add to pinboard
      await StorageService.addPlant(widget.title, pinboardName);
    }
    // Refresh the status
    await _loadPinBoards();
  }

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
            top: 20,
            left: 20,
            right: 20
        ),
        decoration: BoxDecoration(
          color: lightgrey,
          borderRadius: BorderRadius.circular(15),
        ),
        child: Column(
          //mainAxisSize: MainAxisSize.min,
          children: [
            Container(
              child: ClipRRect(
                borderRadius: BorderRadius.only(
                  topLeft: Radius.circular(15),
                  topRight: Radius.circular(15),
                ),
                child: Image(
                  image: AssetImage(widget.imageUrl),
                  height: 150,
                  fit: BoxFit.cover,
                  width: double.infinity ,
                ),
              ),
            ),
            Container(
              child: Padding(
                padding: const EdgeInsets.all(8.0),
                child: Row(
                  //mainAxisSize: MainAxisSize.min,
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,                  //crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Container( // unsichbarer Button, damit Text zentriert ist
                        alignment: Alignment.center,
                        decoration: BoxDecoration(
                          border: Border.all(
                              color: Color.fromARGB(0, 1, 1, 1),
                              width: 2
                          ),
                          //color: buttonColor,
                          borderRadius: BorderRadius.circular(100),
                        ),
                        padding: EdgeInsets.all(7.0),
                        child: Center(
                          child: Icon(
                            addIcon,
                            size: 15,
                            color: Color.fromARGB(0, 1, 1, 1),
                          ),
                        )
                    ),
                    Expanded(
                      child: Center(
                        child: Text(
                          widget.title,
                          style: TextStyle(
                            fontSize: 17,
                          ),
                        ),
                      ),
                    ),
                        PopupMenuButton(
                          child: Icon(
                            pinboardStatus.values.contains(true) ? CupertinoIcons.minus_circle : CupertinoIcons.plus_circle,
                            size: 33,
                            color: pinboardStatus.values.contains(true) ? darkgrey : green
                          ),
                          onSelected: (value) {
                            _togglePlantInPinboard(value);
                            },
                            itemBuilder: (BuildContext context){
                              List<PopupMenuEntry<String>> menuItems = [];
                              menuItems.add(
                                PopupMenuItem<String>(
                                  value: 'Wishlist',
                                  child: Row(
                                    children: [
                                      Padding(
                                        padding: EdgeInsets.only(right: 8.0),
                                        child: Icon(
                                          pinboardStatus['Wishlist'] == true ? Icons.remove : Icons.add,
                                          color: pinboardStatus['Wishlist'] == true ? darkgrey : green,
                                        ),
                                      ),
                                      Text(
                                        pinboardStatus['Wishlist'] == true ? 'aus Wishlist entfernen' : 'zu Wishlist hinzufügen',
                                        style: TextStyle(fontSize: 12),
                                      ),
                                    ],
                                  ),
                                ),
                              );
                              menuItems.addAll(AllPinboards.map((pinboardName) {
                                return PopupMenuItem<String>(
                                  value: pinboardName,
                                  child: Row(
                                    children: [
                                      Padding(
                                        padding: EdgeInsets.only(right: 8.0),
                                        child: Icon(
                                          pinboardStatus[pinboardName] == true ? Icons.remove : Icons.add,
                                          color: pinboardStatus[pinboardName] == true ? darkgrey : green,
                                        ),
                                      ),
                                      Text(
                                        pinboardStatus[pinboardName] == true ? 'aus $pinboardName entfernen' : 'zu $pinboardName hinzufügen',
                                        style: TextStyle(fontSize: 12),
                                      ),
                                    ],
                                  ),
                                );
                              }).toList());

                              return menuItems;
                            },
                      ),
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}