import 'package:bee_bloom/pages/calendar_page.dart';
import 'package:bee_bloom/pages/home_page.dart';
import 'package:bee_bloom/pages/pinboard_page.dart';
import 'package:bee_bloom/pages/search_page.dart';
import 'package:boxicons/boxicons.dart';
import 'package:flutter/material.dart';
import '../constants/sizes.dart';
import '../constants/constants.dart';

class MainPage extends StatefulWidget {
  const MainPage({super.key});

  @override
  State<MainPage> createState() => _MainPageState();
}

class _MainPageState extends State<MainPage> {
  int currentPage = 0;
  PageController pageController = PageController();

  @override
  Widget build(BuildContext context) {
    Sizes.initialize(context);
    return Scaffold(
      backgroundColor: white,
      body: SafeArea(
        child: Column(
          children: [
            Expanded(
              child: PageView(
                physics: NeverScrollableScrollPhysics(),
                controller: pageController,
                children: [
                  HomePage(),
                  SearchPage(),
                  CalendarPage(),
                  PinboardPage(add_new_plant: (){
                    setState(() {
                      currentPage = 1;
                      pageController.jumpToPage(1);
                    });
                  },),
                ],

              ),
            ),
            Container(
              padding: EdgeInsets.only(
                bottom: 12,
                top: 12,
              ),
              decoration: const BoxDecoration(
                color: white,
                boxShadow: [
                  BoxShadow(
                    color: darkgrey,
                    spreadRadius: 5,
                    blurRadius: 7,
                    offset: Offset(0, 2), // changes position of shadow
                  ),
                ]
              ),
              width: double.infinity,
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [

                  GestureDetector(
                    onTap: (){
                      currentPage = 0;
                      pageController.jumpToPage(0);
                      setState(() {

                      });
                    },
                    child: Container(
                      padding: EdgeInsets.all(10),
                      decoration: BoxDecoration(
                        color: currentPage == 0 ? green : white,
                        borderRadius: BorderRadius.circular(50),
                        border: Border.all(
                          color: green,
                          width: 2,
                        ),
                      ),
                      child: Icon(
                        Boxicons.bx_home,
                        color: currentPage == 0 ? white : green,
                      ),
                    ),
                  ),

                  GestureDetector(
                    onTap: (){
                      currentPage = 1;
                      pageController.jumpToPage(1);
                      setState(() {

                      });
                    },
                    child: Container(
                      padding: EdgeInsets.all(10),
                      decoration: BoxDecoration(
                        color: currentPage == 1 ? green : white,
                        borderRadius: BorderRadius.circular(50),
                        border: Border.all(
                          color: green,
                          width: 2,
                        ),
                      ),
                      child: Icon(
                        Boxicons.bx_search,
                        color: currentPage == 1 ? white : green,
                      ),
                    ),
                  ),

                  GestureDetector(
                    onTap: (){
                      currentPage = 2;
                      pageController.jumpToPage(2);
                      setState(() {

                      });
                    },
                    child: Container(
                      padding: EdgeInsets.all(10),
                      decoration: BoxDecoration(
                        color: currentPage == 2 ? green : white,
                        borderRadius: BorderRadius.circular(50),
                        border: Border.all(
                          color: green,
                          width: 2,
                        ),
                      ),
                      child: Icon(
                        Boxicons.bx_calendar,
                        color: currentPage == 2 ? white : green,
                      ),
                    ),
                  ),

                  GestureDetector(
                    onTap: (){
                      currentPage = 3;
                      pageController.jumpToPage(3);
                      setState(() {

                      });
                    },
                    child: Container(
                      padding: EdgeInsets.all(10),
                      decoration: BoxDecoration(
                        color: currentPage == 3 ? green : white,
                        borderRadius: BorderRadius.circular(50),
                        border: Border.all(
                          color: green,
                          width: 2,
                        ),
                      ),
                      child: Icon(
                        Icons.push_pin_outlined,
                        color: currentPage == 3 ? white : green,
                      ),
                    ),
                  ),
                ],
              ),
            )
          ]
        ),
      ),
    );
  }
}
