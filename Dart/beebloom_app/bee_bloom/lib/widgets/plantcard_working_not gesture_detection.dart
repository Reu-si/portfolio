import 'package:bee_bloom/constants/constants.dart';
import 'package:flutter/material.dart';

class Plantcard extends StatefulWidget {
  String title;
  String imageUrl;

  Plantcard({super.key, required this.title, required this.imageUrl});

  @override
  State<Plantcard> createState() => _PlantcardState();
}

class _PlantcardState extends State<Plantcard> {
  Color buttonColor = green;
  IconData  addIcon = Icons.add;

  @override
  Widget build(BuildContext context) {
    return Container(
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
                  GestureDetector(
                    onTap: (){
                      if(addIcon == Icons.add){
                        addIcon = Icons.remove;
                        buttonColor = Colors.grey;
                      } else{
                        addIcon = Icons.add;
                        buttonColor = green;
                      }
                      setState(() {
                        //lädt Seite neu
                      });
                    },
                    child: PopupMenuButton(
                      //child: GestureDetector(
                      //  onTap: (){
                      //    if(addIcon == Icons.add){
                      //      addIcon = Icons.remove;
                      //      buttonColor = Colors.grey;
                      //    } else{
                      //      addIcon = Icons.add;
                      //      buttonColor = Colors.green;
                      //    }
                      //    setState(() {
                      //      //lädt Seite neu
                      //    });
                      //  },
                        child: Container(
                            alignment: Alignment.center,
                            decoration: BoxDecoration(
                              border: Border.all(
                                  color: buttonColor,
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
                                color: buttonColor,
                              ),
                            )
                        ),
                      //),
                      //onSelected: (value) {
                      //  if (value == "add to Wishlist") {
                      //    //add to Wishlist
                      //  }
                      //  else if (value == "add to Balkon") {
                      //    // add to Balkon
                      //  }
                      //  else if (value == "add to Garten") {
                      //    // add to Garten
                      //  }
                      //},
                        itemBuilder: (BuildContext context) => <PopupMenuEntry>[
                          PopupMenuItem(
                            value: "add to Wishlist",
                              child: Row(
                                children: [
                                  Padding(
                                      padding: EdgeInsets.only(
                                          right: 8.0
                                      ),
                                  child: Icon(
                                      addIcon,
                                      color: buttonColor
                                  ),
                                  ),
                                  Text(
                                    'zu Wishlist hinzufügen',
                                    style: TextStyle(
                                    fontSize: 12,
                                    ),
                                  ),
                                ],
                              )
                          ),
                          PopupMenuItem(
                            value: "add to Balkon",
                              child: Row(
                                children: [
                                  Padding(
                                    padding: EdgeInsets.only(
                                        right: 8.0
                                    ),
                                    child: Icon(
                                        addIcon,
                                        color: buttonColor
                                    ),
                                  ),
                                  Text(
                                    'zu Balkon hinzufügen',
                                    style: TextStyle(
                                      fontSize: 12,
                                    ),
                                  ),
                                ],
                          )
                          ),
                          PopupMenuItem(
                              value: "add to Garten",
                              child: Row(
                                children: [
                                  Padding(
                                    padding: EdgeInsets.only(
                                        right: 8.0
                                    ),
                                    child: Icon(
                                        addIcon,
                                        color: buttonColor
                                    ),
                                  ),
                                  Text(
                                    'zu Garten hinzufügen',
                                    style: TextStyle(
                                      fontSize: 12,
                                    ),
                                  ),
                                ],
                              )
                          )
                        ]
                    ),
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}



// show menu()

/*
*
* import 'package:bee_bloom/constants/constants.dart';
import 'package:flutter/material.dart';

class Plantcard extends StatefulWidget {
  String title;
  String imageUrl;

  Plantcard({super.key, required this.title, required this.imageUrl});

  @override
  State<Plantcard> createState() => _PlantcardState();
}

class _PlantcardState extends State<Plantcard> {
  Color buttonColor = green;
  IconData  addIcon = Icons.add;

  @override
  Widget build(BuildContext context) {
    return Container(
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
                    width: double.infinity,
                  ),
                ),
              ),
              Container(
                  child: Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Row(
                      //mainAxisSize: MainAxisSize.min,
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      //crossAxisAlignment: CrossAxisAlignment.start,
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
                        GestureDetector(
                          onTap: () {
                            if (addIcon == Icons.add) {
                              addIcon = Icons.remove;
                              buttonColor = Colors.grey;
                            } else {
                              addIcon = Icons.add;
                              buttonColor = green;
                            }
                            setState(() {
                              //lädt Seite neu
                            });
                            showMenu(
                              context: context,
                              position: RelativeRect.fromSize(
                                Rect.fromCenter(
                                    center: Offset.fromDirection(0.1), width: 100, height: 100
                                ),
                                Size(100, 100),
                              ),
                              items: [
                                PopupMenuItem(
                                    value: "add to Wishlist",
                                    child: Row(
                                      children: [
                                        Padding(
                                          padding: EdgeInsets.only(
                                              right: 8.0
                                          ),
                                          child: Icon(
                                              addIcon,
                                              color: buttonColor
                                          ),
                                        ),
                                        Text(
                                          'zu Wishlist hinzufügen',
                                          style: TextStyle(
                                            fontSize: 12,
                                          ),
                                        ),
                                      ],
                                    )
                                ),
                                PopupMenuItem(
                                    value: "add to Balkon",
                                    child: Row(
                                      children: [
                                        Padding(
                                          padding: EdgeInsets.only(
                                              right: 8.0
                                          ),
                                          child: Icon(
                                              addIcon,
                                              color: buttonColor
                                          ),
                                        ),
                                        Text(
                                          'zu Balkon hinzufügen',
                                          style: TextStyle(
                                            fontSize: 12,
                                          ),
                                        ),
                                      ],
                                    )
                                ),
                                PopupMenuItem(
                                    value: "add to Garten",
                                    child: Row(
                                      children: [
                                        Padding(
                                          padding: EdgeInsets.only(
                                              right: 8.0
                                          ),
                                          child: Icon(
                                              addIcon,
                                              color: buttonColor
                                          ),
                                        ),
                                        Text(
                                          'zu Garten hinzufügen',
                                          style: TextStyle(
                                            fontSize: 12,
                                          ),
                                        ),
                                      ],
                                    )
                                )
                              ],
                            );
                          },

                          child: Container(
                              alignment: Alignment.center,
                              decoration: BoxDecoration(
                                border: Border.all(
                                    color: buttonColor,
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
                                  color: buttonColor,
                                ),
                              )
                          ),
                        ),
                      ],
                    ),
                  )
              )
            ]
        )
    );
  }
}
*
* */