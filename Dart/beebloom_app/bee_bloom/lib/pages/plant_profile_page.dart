import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/services/storage_service.dart';
import 'package:bee_bloom/data/pflanze.dart';
import 'package:bee_bloom/data/pflanzendaten.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class PlantProfilePage extends StatefulWidget {
  String title;
  PlantProfilePage({super.key, required this.title});

  @override
  State<PlantProfilePage> createState() =>
      _PlantProfilePageState();
}

class _PlantProfilePageState extends State<PlantProfilePage> {
  var top = 400.0;
  List<String> AllPinboards = [];
  Map<String, bool> pinboardStatus = {};
  List<String> WishlistPlants = [];
  List<Pflanze> allPlants = List.from(pflanzen);
  Pflanze? calledPlant;
  IconData wishlistIcon = Icons.favorite_outline;

  @override
  void initState() {
    for(int i = 0; i < allPlants.length; i++){
      if (allPlants[i].name == widget.title){
        calledPlant = allPlants[i];
        break;
      }
    }
    super.initState();
    _loadPinBoards();
  }

  Future<void> _loadPinBoards() async {
    List<String> result = await StorageService.getAllPinBoards();
    setState(() {
      AllPinboards = result;
    });
    List<String> wishlistPlants = await StorageService.getAllPlantsinPinboard("Wishlist");
    setState(() {
      WishlistPlants = wishlistPlants;
    });
    if (WishlistPlants.contains("Wishlist." + widget.title)){
      wishlistIcon = Icons.favorite_outlined;
    }
    pinboardStatus['Wishlist'] = WishlistPlants.contains("Wishlist." + widget.title);
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
    return Scaffold(
      bottomNavigationBar: Container(
        color: Colors.white,
        height: 70,
        width: MediaQuery.of(context).size.width,
        child: Column(
          children: [
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 12.0),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  GestureDetector(
                    onTap: () {
                      _showAddOptions(context);
                    },
                    child: Container(
                      height: 55,
                      width: 55,
                      decoration: BoxDecoration(
                          shape: BoxShape.circle, color: green),
                      child: Center(
                          child: Icon(
                        Icons.add,
                        color: Colors.white,
                        size: 26,
                      )),
                    ),
                  ),
                  GestureDetector(
                    onTap: () async{
                      if (wishlistIcon == Icons.favorite_outline){
                        await StorageService.addPlant(widget.title, 'Wishlist');
                        wishlistIcon = Icons.favorite_outlined;
                        setState(() {

                        });
                      }
                      else {
                        await StorageService.deletePlantfromPinboard(widget.title, 'Wishlist');
                        wishlistIcon = Icons.favorite_outline;
                        setState(() {

                        });
                      }
                    },
                    child: Container(
                      height: 55,
                      width: 55,
                      decoration: BoxDecoration(
                          border: Border.all(color: green, width: 1),
                          shape: BoxShape.circle,
                          color: Colors.white),
                      child: Center(
                          child: Icon(
                          wishlistIcon,
                        color: green,
                        size: 26,
                      )),
                    ),
                  ),
                ],
              ),
            )
          ],
        ),
      ),
      body: NestedScrollView(
        headerSliverBuilder: (context, innerBoxIsScrolled) {
          return [
            SliverAppBar(
              automaticallyImplyLeading: false,
              expandedHeight: 400.0,
              floating: false,
              pinned: true,
              flexibleSpace: LayoutBuilder(
                builder: (BuildContext context, BoxConstraints constraints) {
                  top = constraints.biggest.height;
                  return FlexibleSpaceBar(
                    collapseMode: CollapseMode.pin,
                    centerTitle: true,
                    title: top > 100
                        ? SizedBox()
                        : Container(
                            decoration: BoxDecoration(
                              image: DecorationImage(
                                image: AssetImage(calledPlant!.bildpfad),
                                fit: BoxFit.cover,
                              ),
                            ),
                          ),
                    background: Container(
                      decoration: BoxDecoration(
                        image: DecorationImage(
                          image: AssetImage(calledPlant!.bildpfad),
                          fit: BoxFit.cover,
                        ),
                      ),
                      child: Padding(
                        padding: const EdgeInsets.symmetric(horizontal: 16.0),
                        child: Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: [
                            SizedBox(
                              height: 40,
                            ),
                            GestureDetector(
                              onTap: () {
                                Navigator.pop(context);
                              },
                              child: Container(
                                height: 35,
                                width: 45,
                                decoration: BoxDecoration(
                                    shape: BoxShape.circle,
                                    color: white.withOpacity(0.75)),
                                child: Center(child: Icon(Icons.arrow_back)),
                              ),
                            ),
                            Spacer(),
                            Container(
                              height: 66,
                              width: 211,
                              decoration: BoxDecoration(
                                  borderRadius: BorderRadius.circular(22),
                                  color: white.withOpacity(0.75)),
                              child: Center(
                                child: Text(
                                  widget.title,
                                  style: TextStyle(
                                    fontWeight: FontWeight.w600,
                                    fontSize: 32,
                                  ),
                                ),
                              ),
                            ),
                            SizedBox(
                              height: 15,
                            )
                          ],
                        ),
                      ),
                    ),
                  );
                },
              ),
            ),
          ];
        },
        body: Container(
          color: Colors.white,
          child: ListView(
            padding: EdgeInsets.all(16.0),
            children: [
              SizedBox(
                height: 10,
              ),
              detailTile(calledPlant!.heimisch, "images/leaf.png"),
              detailTile(calledPlant!.artenvielfalt, "images/bee.png"),
              detailTile(calledPlant!.sonne, "images/sun.png"),
              detailTile(calledPlant!.trocken, "images/drop.png"),
              detailTile(calledPlant!.pflege, "images/hand.png"),
              detailTile(calledPlant!.aussaat, "images/calendar.png"),
            ],
          ),
        ),
      ),
    );
  }

  Padding detailTile(String title, String image) {
    return Padding(
      padding: const EdgeInsets.only(left: 30, bottom: 16),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.start,
        children: [
          Container(
            height: 50,
            width: 55,
            decoration: BoxDecoration(
                shape: BoxShape.circle,
                color: Color(0xff0b2128).withOpacity(0.1)),
            child: Center(
                child: Image.asset(
              image,
              height: 25,
              width: 25,
            )),
          ),
          Padding(
            padding: EdgeInsets.only(left: 16.0),
            child: Text(
              title,
              style: TextStyle(fontSize: 16),
            ),
          ),
        ],
      ),
    );
  }

  void _showAddOptions(BuildContext context) {
    showModalBottomSheet(
      context: context,
      builder: (BuildContext context) {
        return Container(
          color: white,
          padding: EdgeInsets.all(16.0),
          height: 250,
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                'Pinnwände:',
                style: TextStyle(
                  fontSize: 18,
                  fontWeight: FontWeight.bold,
                ),
              ),
              Expanded(
                child: SingleChildScrollView(
                  child: Column(
                    children: [
                      ListTile(
                        leading: Icon(
                          pinboardStatus['Wishlist'] == true ? Icons.remove : Icons.add,
                          color: pinboardStatus['Wishlist'] == true ? darkgrey : green,
                        ),
                        title: Text(
                          pinboardStatus['Wishlist'] == true ? 'aus Wishlist entfernen' : 'zu Wishlist hinzufügen',
                        ),
                        onTap: () async {
                          Navigator.pop(context);
                  
                          _togglePlantInPinboard('Wishlist');
                          // Add functionality to add to Wishlist
                        },
                      ),
                  ...AllPinboards.map((pinboardName) {
                    return ListTile(
                      leading: Icon(
                        pinboardStatus[pinboardName] == true ? Icons.remove : Icons.add,
                        color: pinboardStatus[pinboardName] == true ? darkgrey : green,
                      ), // You can customize the icon
                      title: Text(
                        pinboardStatus[pinboardName] == true ? 'aus $pinboardName entfernen' : 'zu $pinboardName hinzufügen',
                      ),
                      onTap: () async {
                        Navigator.pop(context);
                        _togglePlantInPinboard(pinboardName);
                      },
                    );
                  }).toList(),
                    ],
                  ),
                ),
              ),
            ],
          ),
        );
      },
    );
  }
}
