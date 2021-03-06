#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
  "Liberation Sans:style=Regular:size=11",
  "Noto Emoji:pizelsize:10:antialias=true:autohint=true",
};

/* Default colors */
/*
  static const char col_gray1[]       = "#222222";
  static const char col_gray2[]       = "#444444";
  static const char col_gray3[]       = "#bbbbbb";
  static const char col_gray4[]       = "#eeeeee";
  static const char col_cyan[]        = "#005577";
  static const char *colors[][3]      = {
  //               fg         bg         border   *
  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
  [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
  };
*/

/* Solarized colors */
static const char col_gray1[]       = "#002b36";
static const char col_gray2[]       = "#002b36";
static const char col_gray3[]       = "#586e75";
static const char col_gray4[]       = "#839496";
static const char col_gray5[]       = "#93a1a1";
static const char col_cyan[]        = "#073642";
static const char *colors[][3]      = {
  /*               fg         bg         border   */
  [SchemeNorm] = { col_gray4, col_gray1, col_cyan},
  [SchemeSel]  = { col_gray5, col_cyan,  col_gray3  },
};
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
  /* class      instance    title       tags mask     isfloating   monitor */
  { "TelegramDesktop", NULL, NULL,        1 << 4,         0,           1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)                                                \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define TERMINAL "st"

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* Run command in terminal */
#define TCMD(cmd) SHCMD(TERMINAL " -e " cmd)
/* Run command and send kill signal to dwmblocks */
#define KCMD(cmd, signum) SHCMD(cmd "; pkill -RTMIN+" signum " dwmblocks" )

static Key keys[] = {
  /* modifier         key        function        argument */
  { MODKEY|ShiftMask, XK_b,      togglebar,      {0} },
  { MODKEY,           XK_Return, spawn,          SHCMD(TERMINAL)},
  { MODKEY,           XK_w,      spawn,          SHCMD("$BROWSER")},
  { MODKEY,           XK_d,      spawn,          SHCMD("dmenu_run")},
  { MODKEY|ShiftMask, XK_d,      spawn,          SHCMD("passmenu")},
  { MODKEY,           XK_e,      spawn,          SHCMD("emacsclient -cn -a ''") },
  { MODKEY|ShiftMask, XK_p,      spawn,          TCMD("ncmpcpp")},
  { MODKEY|ShiftMask, XK_n,      spawn,          SHCMD("networkmanager_dmenu")},
  { MODKEY|ShiftMask, XK_x,      spawn,          SHCMD("slock")},
  { MODKEY|ShiftMask, XK_t,      spawn,          SHCMD("toggletouchpad")},

  { MODKEY,           XK_n,      focusstack,     {.i = +1 } },
  { MODKEY,           XK_p,      focusstack,     {.i = -1 } },
  { MODKEY,           XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,           XK_o,      incnmaster,     {.i = -1 } },
  { MODKEY,           XK_h,      setmfact,       {.f = -0.01} },
  { MODKEY,           XK_l,      setmfact,       {.f = +0.01} },
  { MODKEY|ShiftMask, XK_Return, zoom,           {0} },
  { MODKEY,           XK_Tab,    view,           {0} },
  { MODKEY,           XK_q,      killclient,     {0} },
  { MODKEY|ShiftMask, XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY|ShiftMask, XK_space,  setlayout,      {.v = &layouts[1]} },
  { MODKEY|ShiftMask, XK_m,      setlayout,      {.v = &layouts[2]} },
  { MODKEY|ShiftMask, XK_space,  togglefloating, {0} },
  { MODKEY|ShiftMask, XK_f,      togglefullscr,  {0} },
  { MODKEY,           XK_s,      togglesticky,   {0} },
  { MODKEY,           XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,           XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask, XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask, XK_period, tagmon,         {.i = +1 } },
  /* Media keys */
  { 0,                 XK_Print, spawn,          SHCMD("scrshot")},
  { 0, XF86XK_AudioRaiseVolume, spawn, KCMD("pamixer -i 2", "10")},
  { 0, XF86XK_AudioLowerVolume, spawn, KCMD("pamixer -d 2", "10")},
  { 0, XF86XK_MonBrightnessUp,  spawn, SHCMD("xbacklight -steps 50 -time 150 -inc 5")},
  { 0, XF86XK_MonBrightnessDown,spawn, SHCMD("xbacklight -steps 50 -time 150 -dec 5")},
  /* Toggle keyboard layout (Mapped as F13 in QMK) */
  { 0, XF86XK_Launch5,            spawn, KCMD("setlang", "11")},

  TAGKEYS(XK_1,       0)
  TAGKEYS(XK_2,       1)
  TAGKEYS(XK_3,       2)
  TAGKEYS(XK_4,       3)
  TAGKEYS(XK_5,       4)
  {MODKEY,            XK_6,      view,           {.ui = ~0 }},

  { MODKEY|ShiftMask, XK_q,      quit,           {0} }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
