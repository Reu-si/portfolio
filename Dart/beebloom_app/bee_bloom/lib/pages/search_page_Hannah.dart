import 'package:bee_bloom/constants/constants.dart';
import 'package:bee_bloom/constants/sizes.dart';
import 'package:flutter/material.dart';

class SearchPage extends StatefulWidget {
  const SearchPage({super.key});

  @override
  State<SearchPage> createState() => _SearchPageState();
}

class _SearchPageState extends State<SearchPage> {
  @override
  Widget build(BuildContext context) {
    return Container(
      child: Padding(
        padding: EdgeInsets.all(Sizes.paddingSmall),
        child: Column(
          children: [
            Container(
              decoration: BoxDecoration(
                border: Border.all(
                    color: green,
                    width: 2,
                ),
                borderRadius: BorderRadius.circular(100),
              ),
                child: SearchBar(
                  //backgroundColor: white,
                )
            )
          ],
        ),
      ),
    );
  }
}
