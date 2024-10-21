#include "labirinto.h"

void printInventory(Item *inventory) {
    Item *current = inventory;
    printf("Inventory: ");
    if (current == NULL) {
        printf("[]\n");
    } else {
        while (current) {
            printf("[%s] -> ", current->name);
            current = current->next;
        }
    }
}

void collectItem(Room *room, Player *player) {
    if (room->items != NULL) {
        Item *itemToCollect = room->items;
        room->items = room->items->next;
        itemToCollect->next = player->inventory;
        player->inventory = itemToCollect;
        printf("Você coletou: %s\n", itemToCollect->name);
    } else {
        printf("Não há itens nesta sala.\n");
    }
}

void addItemToRoom(Room *room, Item item) {
    if (room == NULL)return;
    Item *newItem = createItemList(item.id, item.name);
    newItem->next = room->items;
    room->items = newItem;
}

void addSpellToRoom(Room *room, Spell *spell){
	if(room == NULL || spell == NULL) return;
	room->spell = spell;
}

Item* createItemList(int id, char *name) {
    Item *newItem = (Item*) malloc(sizeof(Item));
    newItem->id = id;
    newItem->name = strdup(name);
    newItem->next = NULL;
    return newItem;
}

bool playerHasItem(Player *player, int itemId) {
    Item *current = player->inventory;
    while (current != NULL) {
        if (current->id == itemId) {
            return true;
        }
        current = current->next;
    }
    return false;
}
