# DP-Week2-Task2 — Deicide: Core Loop Skeleton

**Nama:** Omar Ginza | **NRP:** 5224600063  
**Course:** Design Patterns — Week 2

---

## Cara Build & Jalankan

```bash
cd "C:\Ginza\Unity Project\DP-Week2-5224600063-Omar-Ginza\Task2"
g++ -std=c++17 main.cpp -o Deicide
.\Deicide.exe
```

---

## Struktur File

```
Task2/
│
├── main.cpp                      ← Merakit & inject semua komponen ke GameSession
│
├── [INVARIANT]
│   └── GameSession.h             ← Menjaga urutan 6 fase.
│
├── [INTERFACE — kontrak tiap fase]
│   ├── ICard.h                   ← Kontrak data kartu (nama, Journey, Cycle)
│   ├── IHandGenerator.h          ← Phase 1: generate hand
│   ├── ICardSelector.h           ← Phase 2: player pilih kartu
│   ├── IBondRule.h               ← Phase 3: terapkan bond
│   ├── IScoringRule.h            ← Phase 4: hitung score
│   ├── IWinCondition.h           ← Phase 5: evaluasi menang/kalah
│   └── IShopSystem.h             ← Phase 6: buka shop
│
└── [IMPLEMENTASI PLACEHOLDER]
    ├── DeicideCard.h             ← Kartu dengan nilai Journey & Cycle
    ├── ScriptedHandGenerator.h   ← Phase 1: kartu scripted per round
    ├── AutoCardSelector.h        ← Phase 2: otomatis mainkan semua kartu
    ├── DeicideBondRule.h         ← Phase 3: deteksi & terapkan 3 bond demo
    ├── DeicideScoringRule.h      ← Phase 4: score = totalJourney x totalCycle
    ├── DeicideWinCondition.h     ← Phase 5: menang jika score >= goal
    └── DeicideShopSystem.h       ← Phase 6: placeholder Kremnos/Okhema Pack
```

---

## Step 1 — Core Loop

```
1. System generate hand kartu untuk player
2. Player memilih kartu yang akan dimainkan
3. System memeriksa dan menerapkan Bond yang aktif
4. System menghitung score: totalJourney x totalCycle
5. System mengevaluasi hasil: WIN jika score >= goal, GAME OVER jika tidak
6. Jika WIN → buka Shop untuk upgrade kartu atau bond
7. Goal naik x1.5, lanjut ke round berikutnya
8. Repeat dari langkah 1
```

---

## Step 2 — Invariant

### Langkah yang tidak boleh berubah urutannya

| Urutan | Fase | Alasan |
|---|---|---|
| 1 | Generate hand | Kartu harus ada sebelum player bisa memilih |
| 2 | Player pilih kartu | Input player harus diterima sebelum sistem memproses apapun |
| 3 | Apply bond | Bond hanya berlaku pada kartu yang dipilih, bukan seluruh hand |
| 4 | Compute score | Score dihitung setelah bond diterapkan — jika terbalik, efek bond tidak masuk |
| 5 | Evaluasi hasil | Hanya bisa dievaluasi setelah score final diketahui |
| 6 | Shop | Hanya terbuka jika player menang — tidak boleh sebelum evaluasi |

### Komponen yang wajib selalu ada

Semua 6 interface harus tersedia saat `GameSession` dibuat. Tanpa salah satu dari mereka, game loop tidak bisa berjalan sampai selesai. `GameSession` sendiri tidak boleh dimodifikasi untuk alasan apapun — ia hanya memanggil interface dalam urutan yang benar.

### Yang rusak jika urutan berubah

Bond sebelum pilih kartu — buff masuk ke seluruh hand, bukan hanya kartu yang dimainkan. Score sebelum bond — efek semua bond tidak pernah dihitung. Shop sebelum evaluasi — player bisa upgrade meski kalah, menghilangkan seluruh konsekuensi kekalahan.

---

## Step 3 — Mutable Elements

Semua 6 interface bersifat mutable. Untuk mengganti implementasi apapun, cukup buat class baru yang implements interface-nya, lalu swap di `main.cpp`. `GameSession` tidak perlu disentuh.

| Interface | Implementasi Sekarang | Contoh Ekspansi |
|---|---|---|
| `IHandGenerator` | `ScriptedHandGenerator` — kartu tetap per round | `RandomHandGenerator` — ambil dari Deck secara random |
| `ICardSelector` | `AutoCardSelector` — mainkan semua otomatis | `PlayerInputSelector` — baca input keyboard dari player |
| `IBondRule` | `DeicideBondRule` — 3 bond demo | Class terpisah per bond, semua di-inject via vector |
| `IScoringRule` | `DeicideScoringRule` — Journey x Cycle | Rumus scoring alternatif |
| `IWinCondition` | `DeicideWinCondition` — score >= goal | Survival mode, batas round, dll |
| `IShopSystem` | `DeicideShopSystem` — placeholder skip | Toko interaktif dengan dua jenis pack |

Contoh konkrit: untuk upgrade dari scripted ke implementasi penuh, hanya dua baris di `main.cpp` yang berubah:

```cpp
// Sekarang (scripted demo):
ScriptedHandGenerator generator;
AutoCardSelector      selector;

// Nanti (implementasi penuh):
RandomHandGenerator   generator(deck);
PlayerInputSelector   selector;

// GameSession tidak disentuh sama sekali:
GameSession session(&generator, &selector, &bond, &scoring, &win, &shop, 300);
```

---

## Step 4 — C++ Core Loop Skeleton

`GameSession` hanya menyimpan pointer ke 6 interface dan memanggil mereka dalam urutan yang terkunci. Tidak ada `virtual`, tidak ada `protected`, tidak ada subclass.

```cpp
class GameSession {
    IHandGenerator* handGenerator;  // Phase 1
    ICardSelector*  cardSelector;   // Phase 2
    IBondRule*      bondRule;       // Phase 3
    IScoringRule*   scoringRule;    // Phase 4
    IWinCondition*  winCondition;   // Phase 5
    IShopSystem*    shopSystem;     // Phase 6

public:
    void Start() {
        while (isRunning) {
            Phase_GenerateHand(hand);            // Phase 1
            Phase_SelectCards(hand, selected);   // Phase 2
            Phase_ApplyBonds(selected);          // Phase 3
            int  score = Phase_ComputeScore(selected);  // Phase 4
            bool won   = Phase_EvaluateResult(score);   // Phase 5
            if (won) Phase_OpenShop();                  // Phase 6
        }
    }
};
```

Tiap `Phase_X()` adalah private method yang hanya memanggil satu method dari interface yang sesuai — tidak ada logika lain di dalamnya.

---

## Contoh Output

```
============================================
           DEICIDE -- RUN
============================================

--------------------------------------------
 Round 1  |  Goal: 300
--------------------------------------------
[Phase 1] Generate Hand
  Hand dealt:
    + Kephale  J:100  C:1
    + Nikador  J:80   C:1
    + Thanatos J:40   C:2
[Phase 2] Player Selects Cards
  (scripted: play all 3 cards)
[Phase 3] Apply Bonds
  [BOND] HEATED RIVALRY activated
         Kephale & Nikador are rivals -- each gains +100 Journey
         Kephale Journey: 100 -> 200
         Nikador Journey: 80  -> 180
[Phase 4] Compute Score
  totalJourney=420  totalCycle=4  =>  Score = 420 x 4 = 1680
[Phase 5] Evaluate Result
  score 1680  vs  goal 300

  >> WIN  (score 1680 >= goal 300)
[Phase 6] Open Shop
  [Kremnos Pack]  upgrade Journey/Cycle kartu pilihan
  [Okhema Pack]   upgrade nilai buff salah satu bond
  (placeholder -- shop skipped)

--------------------------------------------
 Round 4  |  Goal: 1012
--------------------------------------------
...
[Phase 3] Apply Bonds
  (no bonds active for this hand)
[Phase 4] Compute Score
  totalJourney=15  totalCycle=10  =>  Score = 15 x 10 = 150
[Phase 5] Evaluate Result
  score 150  vs  goal 1012

  >> GAME OVER  (score 150 < goal 1012)
```

Skenario tiap round di `ScriptedHandGenerator`:
- **Round 1** — Kephale + Nikador + Thanatos → **HEATED RIVALRY** aktif (+100 Journey tiap kartu)
- **Round 2** — Janus + Talanton + Oronyx → **TITAN FATE** aktif (+6 Cycle tiap kartu FATE)
- **Round 3** — Demiurge + Kephale + Georios → **CYCLE BEGINNING** aktif (+500 Journey Kephale)
- **Round 4** — hand lemah tanpa bond → **GAME OVER**

---

## Refleksi

### 1. Apa invariant structure dari game ini?

Invariant adalah urutan 6 fase yang dikunci di dalam `GameSession::Start()`. `GameSession` menyimpan pointer ke 6 interface dan memanggil mereka dalam urutan yang sama setiap round tanpa pengecualian. Tidak ada satu pun class konkrit yang dikenal oleh `GameSession` — ia tidak tahu kartu apa yang digunakan, bagaimana hand dibentuk, bond apa yang aktif, rumus scoring yang dipakai, kondisi menang yang berlaku, atau mekanik toko yang tersedia. Semua itu adalah urusan implementasi yang di-inject dari luar. Selama `GameSession` tidak dimodifikasi, urutan fase dan struktur loop terjaga sepenuhnya apapun yang di-inject.

### 2. Bagian mana yang mutable?

Semua 6 implementasi konkrit yang di-inject bersifat mutable. `ScriptedHandGenerator` bisa diganti dengan `RandomHandGenerator` yang mengambil kartu dari Deck nyata. `AutoCardSelector` bisa diganti dengan `PlayerInputSelector` yang membaca input keyboard. `DeicideBondRule` bisa dikembangkan menjadi 15 class bond terpisah yang masing-masing di-inject. `DeicideScoringRule` bisa diganti dengan rumus apapun. `DeicideWinCondition` bisa diganti dengan mode permainan berbeda. Dalam semua kasus, penggantian cukup dilakukan di `main.cpp` saat merakit komponen.

### 3. Jika ingin menambah fitur baru, class mana yang berubah?

Bergantung pada fiturnya. Untuk hand random dari Deck: buat `RandomHandGenerator` implements `IHandGenerator`, swap di `main.cpp`. Untuk input player nyata: buat `PlayerInputSelector` implements `ICardSelector`, swap di `main.cpp`. Untuk bond baru: tambah deteksi di `DeicideBondRule` atau buat class terpisah per bond. Untuk mekanik shop interaktif: kembangkan `DeicideShopSystem`. `GameSession` tidak pernah perlu disentuh karena ia hanya tahu interface, bukan implementasi.

### 4. Jika urutan loop diubah, apa yang rusak?

Jika bond diterapkan sebelum player memilih kartu, buff akan masuk ke seluruh hand bukan hanya kartu yang dimainkan sehingga player mendapat keuntungan gratis setiap giliran. Jika score dihitung sebelum bond, efek semua bond tidak pernah masuk ke angka akhir sehingga seluruh sistem bond menjadi dekoratif. Jika shop dibuka sebelum hasil dievaluasi, player bisa upgrade bahkan saat kalah dan seluruh konsekuensi kekalahan hilang. Setiap fase bergantung langsung pada output fase sebelumnya — bukan sekadar urutan gaya penulisan.
