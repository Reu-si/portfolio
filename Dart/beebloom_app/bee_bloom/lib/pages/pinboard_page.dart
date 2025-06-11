import 'dart:ui';

import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/constants/sizes.dart';
import 'package:bee_bloom/services/storage_service.dart';
import 'package:bee_bloom/widgets/pinboard.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class PinboardPage extends StatefulWidget {
  VoidCallback add_new_plant;

  PinboardPage({super.key, required this.add_new_plant});

  @override
  State<PinboardPage> createState() => _PinboardPageState();
}

class _PinboardPageState extends State<PinboardPage> {
  List<String> AllPinboards = [];
  final TextEditingController _textFieldController = TextEditingController();

  @override
  void initState() {
    StorageService.getAllPinBoards().then((List<String> result){
      AllPinboards = result;
      setState(() {

      });
    });
    super.initState();
  }
  @override
  Widget build(BuildContext context) {
    return Container(
      child: Column(
        children: [
          Expanded(
            child: SingleChildScrollView(
              child: Column(
                children: List.generate(AllPinboards.length + 1, (int i){
                  if(i == 0){
                    return Pinboard(pinboardname: "Wishlist", pinboardliste: [], add_new_plant: widget.add_new_plant, deletePinboard: (){});
                  }else{
                    return Pinboard(pinboardname: AllPinboards[i - 1], pinboardliste: [], add_new_plant: widget.add_new_plant, deletePinboard: () async{
                      await StorageService.deletePinBoard(AllPinboards[i-1]);
                      StorageService.getAllPinBoards().then((List<String> result){
                        setState(() {
                          AllPinboards = result;

                        });
                      });
                    });
                  }
                }) ,
              ),
            ),
          ),
          Container(
            padding: EdgeInsets.only(
              bottom: Sizes.paddingSmall,
              top: Sizes.paddingSmall,
            ),
            child: Column (
              children: [
                Text(
                  "Neue Pinnwand hinzufügen",
                  style: TextStyle(
                    fontSize: 15,
                    fontWeight: FontWeight.bold,
                    color: darkgrey,
                  ),
                ),
                GestureDetector(
                  onTap: () async{
                    await _displayTextInputDialog(context);
                    String pinBoardName = _textFieldController.text;
                    await StorageService.addPinBoard(pinBoardName);
                    StorageService.getAllPinBoards().then((List<String> result){
                      AllPinboards = result;
                      setState(() {

                      });
                    });
                  },
                  child: Icon(
                    CupertinoIcons.plus_circle,
                    size: 40,
                    color: green,
                  ),
                )
              ],
            ),
          )
        ],
      ),
    );
  }

  Future<void> _displayTextInputDialog(BuildContext context) async {
    return showDialog(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: Text('Pinnwand Hinzufügen'),
          content: TextField(
            controller: _textFieldController,
            decoration: InputDecoration(hintText: "Name der Pinnwand"),
          ),
          actions: <Widget>[
            TextButton(
              child: Text('ABBRECHEN'),
              onPressed: () {
                Navigator.pop(context);
              },
            ),
            TextButton(
              child: Text('OK'),
              onPressed: () {
                Navigator.pop(context);
              },
            ),
          ],
        );
      },
    );
  }

}
